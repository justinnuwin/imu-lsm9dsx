OUTPUT_DIR=build
.PHONY: all install uninstall clean

all: lib imu_test

python_interface: lib imu_server
	$(MAKE) -C python_lsm9dsx python_interface

lib:
	$(MAKE) -C src all

imu_test:
	$(MAKE) -C tools/$@
	cp tools/$@/$@ $(OUTPUT_DIR)/

imu_server:
	$(MAKE) -C tools/$@
	cp tools/$@/$@ $(OUTPUT_DIR)/

install:
	cp $(OUTPUT_DIR)/*.a /usr/local/lib
	cp $(OUTPUT_DIR)/*.h /usr/local/include

install_python_interface:
	cp $(OUTPUT_DIR)/imu_server /usr/local/bin
	$(MAKE) -C python_lsm9dsx install

uninstall:
	rm -f /usr/local/lib/liblsm9ds*.a 
	rm -f /usr/local/include/lsm9ds*.h

uninstall_python_interface:
	rm -f /usr/local/bin/imu_server
	$(MAKE) -C python_lsm9dsx uninstall

clean:
	$(MAKE) -C src clean
	rm -f $(OUTPUT_DIR)/imu_test
	rm -f $(OUTPUT_DIR)/imu_server
	rm -rf $(OUTPUT_DIR)
	$(MAKE) -C python_lsm9dsx clean
