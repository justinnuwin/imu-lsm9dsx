CC=gcc
AR=ar
CFLAGS=-Wall -Werror -g
OUTPUT_DIR=../build

.PHONY: setup clean 

all: setup liblsm9ds0.a liblsm9ds1.a
	cp lsm9dsx.h $(OUTPUT_DIR)/
	cp lsm9ds0.h $(OUTPUT_DIR)/
	cp lsm9ds1.h $(OUTPUT_DIR)/

liblsm9ds0.a: lsm9ds0.o i2c.o
	$(AR) -rcs $(OUTPUT_DIR)/$@ $^

liblsm9ds1.a: lsm9ds1.o i2c.o
	$(AR) -rcs $(OUTPUT_DIR)/$@ $^

lsm9ds0.o: lsm9dsx.c lsm9dsx.h lsm9ds0.h
	$(CC) -o $@ $(CFLAGS) -DSERIES0 -c $<

lsm9ds1.o: lsm9dsx.c lsm9dsx.h lsm9ds1.h
	$(CC) -o $@ $(CFLAGS) -DSERIES1 -c $<

i2c.o: i2c.c i2c.h
	$(CC) -o $@ $(CFLAGS) -c $<

setup:
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f *.o
	rm -f $(OUTPUT_DIR)/*.o
	rm -f $(OUTPUT_DIR)/lsm9dsx.h 
	rm -f $(OUTPUT_DIR)/lsm9ds0.h 
	rm -f $(OUTPUT_DIR)/lsm9ds1.h 

