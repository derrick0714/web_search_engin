SRC_DIR= $(CURDIR)/src
MAKE_DIR= $(CURDIR)
OBJ_DIR= ./build
DIST_DIR= ../dist
INSTALL_PREFIX= ../test


.SUFFIXES: 

all:

%:
	[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(MAKE) -C $(OBJ_DIR) -f $(MAKE_DIR)/Makefile.include \
							MAKE_DIR=$(CURDIR) \
							SRC_DIR=$(SRC_DIR) \
							DIST_DIR=$(DIST_DIR) \
							INSTALL_PREFIX=$(INSTALL_PREFIX) \
							$@
