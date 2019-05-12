TOPDIR:=../../..

LDLIBS:= \
	-lprism-switch-client \
	`pkg-config --libs protobuf` \
	-luv \
	-ltomcrypt \
	-ltfm \
	-lleveldb \
	-lssl \
	-lcrypto

include $(TOPDIR)/src/Makefile.inc

OBJS:=phttp_kvs_backend.o phttp_kvs_proxy.o
TARGETS:= phttp-kvs-backend phttp-kvs-proxy

all: $(TARGETS)

phttp-kvs-backend: phttp_kvs_backend.o $(TOPDIR)/src/libphttp.a
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

phttp-kvs-proxy: phttp_kvs_proxy.o $(TOPDIR)/src/libphttp.a
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

clean:
	- rm $(TARGETS) $(OBJS)
