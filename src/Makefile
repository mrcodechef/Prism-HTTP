TOPDIR:=..

include Makefile.inc

CPPFLAGS+= \
	`pkg-config --cflags grpc grpc++ protobuf` \
	-DTFM_DESC \
	-DUSE_TFM \
	-DTLS_REEXPORTABLE \
	-DWITH_KTLS \
	-DTLS_RX

CFLAGS+=$(CPPFLAGS)

HOPROTO_OBJ:= \
	phttp_hoproto_export2.o \
	phttp_hoproto_import2.o \
	phttp_hoproto_close2.o

OBJS:= \
	cpp_gen/tcp.pb.o \
	tcp_export.o \
	cpp_gen/tls.pb.o \
	tls_export.o \
	cpp_gen/http.pb.o \
	http_export.o \
	extern/picohttpparser.o \
	extern/tlse.o \
	http.o \
	uv_tcp_monitor.o \
	phttp_argparse.o \
	phttp_handoff_server.o \
	phttp_server.o \
	phttp_prof.o

OBJS+=$(HOPROTO_OBJ)

TARGETS:= libphttp.a

all: $(TARGETS) apps

libphttp.a: $(OBJS)
	ar rc $@ $^

apps: libphttp.a
	make -C apps all

clean:
	- rm -f $(OBJS) $(TARGETS)
	- make -C apps clean

.PHONY: all clean apps
