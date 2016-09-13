DEFINES+=PROJECT_CONF_H=\"project-conf.h\"
MODULES += dev/enc28j60 core/net/ip64

CONTIKI_WITH_IPV6 = 1
CFLAGS += -DWITH_IP64=1

all: ip64-router

CONTIKI=../../..

include $(CONTIKI)/Makefile.include

