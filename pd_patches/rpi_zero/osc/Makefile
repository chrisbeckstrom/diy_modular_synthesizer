# Makefile for osc

lib.name = osc

class.sources = packOSC.c pipelist.c routeOSC.c unpackOSC.c

datafiles = packOSC-help.pd pipelist-help.pd routeOSC-help.pd unpackOSC-help.pd \
            packOSCstream.pd packOSCstream-help.pd unpackOSCstream.pd \
            unpackOSCstream-help.pd \
            osc-meta.pd LICENSE.txt README.txt

define forWindows
  ldlibs = -lwsock32
endef

# This Makefile is based on the Makefile from pd-lib-builder written by
# Katja Vetter. You can get it from:
# https://github.com/pure-data/pd-lib-builder

include ../pd-lib-builder/Makefile.pdlibbuilder
