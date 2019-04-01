HOPROTO:=2

CPPFLAGS:= \
	-g \
	-Ofast \
	-I $(TOPDIR)/src/include \
	-I $(TOPDIR)/switch$(HOPROTO)/include \
	-L $(TOPDIR)/switch$(HOPROTO)/lib \
	-Wall \
	-Wno-write-strings \
	-DHOPROTO=$(HOPROTO) \
  -DNO_SSL_COMPATIBLE_INTERFACE \
  -fsanitize=address
