
all:
	-$(MAKE) -C sandbox clean
	$(MAKE) -C sandbox -j16

build:
	$(MAKE) -C sandbox -j16

clean:
	$(MAKE) -C sandbox clean