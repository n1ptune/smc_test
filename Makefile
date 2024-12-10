# Top-level Makefile
.PHONY: all driver user clean

all: driver user 

user:
	$(MAKE) -C user

driver:
	$(MAKE) -C driver

clean:
	$(MAKE) -C user clean
	$(MAKE) -C driver clean