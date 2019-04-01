#include <cstdio>
#include <errno.h>
#include <linux/tcp.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <assert.h>

#include <uv_tcp_monitor.h>

int
uv_tcp_monitor_init(uv_loop_t *loop, uv_tcp_monitor_t *monitor, uv_tcp_t *tcp)
{
  int evfd, error, sock;

  if (loop == NULL || monitor == NULL || tcp == NULL) {
    return -EINVAL;
  }

  uv_fileno((uv_handle_t *)tcp, &sock);

  evfd = eventfd(0, 0);
  if (evfd == -1) {
    return -errno;
  }

  error = setsockopt(sock, IPPROTO_TCP, TCP_MONITOR_SET_EVENTFD, &evfd,
                     sizeof(int));
  if (error) {
    error = -errno;
    goto err0;
  }

  error = uv_poll_init(loop, (uv_poll_t *)monitor, evfd);
  if (error) {
    goto err0;
  }

  monitor->tcp = tcp;

  return 0;

err0:
  close(evfd);
  return error;
}

static void
uv_tcp_monitor_on_tcp_close(uv_poll_t *handle, int status, int events)
{
  int fd;

  if (status < 0) {
    fprintf(stderr, "%s", uv_strerror(status));
  }

  if (!(events & UV_READABLE)) {
    fprintf(stderr, "Unexpected event %d detected\n", events);
  }

  uv_fileno((uv_handle_t *)handle, &fd);

  uint64_t counter;
  ssize_t rsize;
  rsize = read(fd, &counter, sizeof(counter));
  assert(rsize == sizeof(counter));
  assert(counter == 1);

  uv_tcp_monitor_t *monitor = (uv_tcp_monitor_t *)handle;
  monitor->saved_close(monitor);
}

int
uv_tcp_monitor_schedule_close(uv_tcp_monitor_t *monitor, uv_tcp_monitor_cb cb)
{
  int error;

  if (monitor == NULL) {
    return -EINVAL;
  }

  error = uv_poll_start((uv_poll_t *)monitor, UV_READABLE,
                        uv_tcp_monitor_on_tcp_close);
  if (error) {
    return error;
  }

  monitor->saved_close = cb;
  uv_close((uv_handle_t *)monitor->tcp, NULL);

  return 0;
}
