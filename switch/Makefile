INSTALL_PREFIX=/usr/local

CXXFLAGS:= \
	`pkg-config --cflags libbcc` \
	-I include \
	-fPIC \
	-Wall \
	-g \
	-Ofast

LDFLAGS:= \
	`pkg-config --libs grpc++ protobuf libbcc`

TARGETS:= bin/prism_switchd lib/libprism-switch-client.a

all: $(TARGETS)

bin/prism_switchd: src/cpp/prism_switchd.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

lib/libprism-switch-client.a: src/cpp/prism_switch_client.o
	ar rc $@ $^

clean:
	- rm -f $(OBJS) src/cpp/prism_switchd.o src/cpp/prism_switch_client.o $(TARGETS)
