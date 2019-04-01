INSTALL_PREFIX=/usr/local

OBJS:= \
	src/cpp/prism_switch.pb.o \
	src/cpp/prism_switch.grpc.pb.o

CXXFLAGS:= \
	`pkg-config --cflags protobuf grpc libbcc` \
	-I include \
	-fPIC \
	-Wall \
	-g \
	-Ofast

LDFLAGS:= \
	`pkg-config --libs grpc++ protobuf libbcc` \

TARGETS:= bin/prism_switchd lib/libprism-switch-client.a

all: $(TARGETS)

bin/prism_switchd: $(OBJS) src/cpp/prism_switchd.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

lib/libprism-switch-client.a: $(OBJS) src/cpp/prism_switch_client.o
	ar rc $@ $^

install:
	install -D bin/prism_switchd $(INSTALL_PREFIX)/bin
	install -D lib/libprism-switch-client.a $(INSTALL_PREFIX)/lib
	install -D include/prism_switch/prism_switch_client.h $(INSTALL_PREFIX)/include/prism_switch/prism_switch_client.h
	install -D include/prism_switch/prism_switch.h $(INSTALL_PREFIX)/include/prism_switch/prism_switch.h
	install -D include/vale_bpf_native/vale_bpf_native_api.h $(INSTALL_PREFIX)/include/vale_bpf_native/vale_bpf_native_api.h
	install -D include/vale_bpf_native/vale_bpf_native.h $(INSTALL_PREFIX)/include/vale_bpf_native/vale_bpf_native.h

clean:
	- rm -f $(OBJS) src/cpp/prism_switchd.o src/cpp/prism_switch_client.o $(TARGETS)
