# Prism

Research prototype

All sources are published under Apache2 license unless there is no license text on top of the file.

## How to run benchmark applications

### Setup Vagrant environment

```
# On top of this repo
vagrant up --provider libvirt
```

We observe sometimes the Vagrant fails to provision the nodes unexpectedly. In that case, destroy
the nodes and retrying usually worked for us.

### Run `phttp-bench` application

`phttp-bench` is an application which is useful for measuring the effect of the TCP handoff. Client specifies the sizeof the object to down load by path like `/1000` . The unit is byte. Frontend just handoff the requests to the backends without any processing and the backends send the respond with on-memory random bytes.

#### Setup switch

```
# On switch node
cd /home/vagrant/Prism-HTTP/switch
sudo ./bin/prism_switchd -s vale0 -I $(pwd)/include -f src/cpp/prism_switch.bpf.c -a 172.16.10.10:18080
```

#### Setup frontend

```
# On frontend1 node
sudo phttp-bench-proxy --addr 172.16.10.11 --port 80 --mac 02:00:00:00:00:01 --backlog 8192 --ho-addr 172.16.10.11 --ho-port 8080 --ho-backlog 64 --sw-addr 172.16.10.10 --sw-port 18080 --backends 172.16.10.12:8080,172.16.10.13:8080 --nworkers 1
```

#### Setup backends

```
# On backend1 node
sudo phttp-bench-backend --addr 172.16.10.12 --port 80 --mac 02:00:00:00:00:02 --backlog 8192 --ho-addr 172.16.10.12 --ho-port 8080 --ho-backlog 64 --sw-addr 172.16.10.10 --sw-port 18080 --proxy-addr 172.16.10.11 --proxy-port 8080 --nworkers 1

# On backend2 node
sudo phttp-bench-backend --addr 172.16.10.13 --port 80 --mac 02:00:00:00:00:03 --backlog 8192 --ho-addr 172.16.10.13 --ho-port 8080 --ho-backlog 64 --sw-addr 172.16.10.10 --sw-port 18080 --proxy-addr 172.16.10.11 --proxy-port 8080 --nworkers 1
```

#### Run test

```
# On client node
curl http://172.16.10.11/1000  # Download the 1K objects
```

