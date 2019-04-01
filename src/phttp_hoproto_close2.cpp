#include <cassert>
#include <unistd.h>
#include <phttp_server.h>

static void
after_close_tcp_monitor(uv_handle_t *_monitor)
{
  uv_tcp_monitor_t *monitor = (uv_tcp_monitor_t *)_monitor;
  uv_tcp_t *client = monitor->tcp;
  http_client_socket_t *hcs = (http_client_socket_t *)client->data;

  free(client);
  http_client_socket_deinit(hcs);
  free(hcs);
}

static void
after_close_imported_tcp(uv_tcp_monitor_t *monitor)
{
  int error;
  uv_tcp_t *client = monitor->tcp;
  http_client_socket_t *hcs = (http_client_socket_t *)client->data;
  struct global_config *gconf = (struct global_config *)client->loop->data;
  prism_switch_client_t *sw_client = gconf->sw_client;

  /*
   * Cleanup switch rule
   */
  struct psw_delete_req del_req;

  del_req.type = PSW_REQ_DELETE;
  del_req.status = 0;
  del_req.peer_addr = hcs->peername_cache.peer_addr;
  del_req.peer_port = hcs->peername_cache.peer_port;

  error = prism_switch_client_queue_task(
      sw_client, (struct psw_req_base *)&del_req, NULL, NULL);
  assert(error == 0);

  /*
   * Cleanup all client states
   */
  int evfd;
  uv_poll_stop((uv_poll_t *)monitor);
  uv_fileno((uv_handle_t *)monitor, &evfd);
  close(evfd);
  uv_close((uv_handle_t *)monitor, after_close_tcp_monitor);
}

static void
after_close_tcp(uv_tcp_monitor_t *monitor)
{
  uv_close((uv_handle_t *)monitor, after_close_tcp_monitor);
}

int
phttp_start_close(uv_tcp_t *client)
{
  int error;
  http_client_socket_t *hcs = (http_client_socket_t *)client->data;

  if (hcs->imported) {
    error =
        uv_tcp_monitor_schedule_close(&hcs->monitor, after_close_imported_tcp);
    assert(error == 0);
  } else {
    error = uv_tcp_monitor_schedule_close(&hcs->monitor, after_close_tcp);
    assert(error == 0);
  }

  return 0;
}
