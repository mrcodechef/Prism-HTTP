TOPDIR:=../../..

LDLIBS:= \
	-lprism-switch-client \
	`pkg-config --libs grpc grpc++ protobuf` \
	-luv \
	-ltomcrypt \
	-ltfm

include $(TOPDIR)/src/Makefile.inc

OBJS:= phttp_bench_backend.o phttp_bench_proxy.o
TARGETS:= phttp-bench-backend phttp-bench-proxy

all: $(TARGETS)

phttp-bench-backend: phttp_bench_backend.o $(TOPDIR)/src/libphttp.a
	$(CXX) $(CPPFLAGS) -DPHTTP_DEBUG -o $@ $^ $(LDLIBS)

phttp-bench-proxy: phttp_bench_proxy.o $(TOPDIR)/src/libphttp.a
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

clean:
	- rm $(TARGETS) $(OBJS)
