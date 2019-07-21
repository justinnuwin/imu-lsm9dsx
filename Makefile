OUTPUT_DIR=build
.PHONY: all install uninstall clean

all:
	$(MAKE) -C src all

install:
	cp $(OUTPUT_DIR)/*.a /usr/local/lib
	cp $(OUTPUT_DIR)/*.h /usr/local/include

uninstall:
	rm -f /usr/local/lib/liblsm9ds*.a 
	rm -f /usr/local/include/lsm9ds*.h

clean:
	$(MAKE) -C src clean
