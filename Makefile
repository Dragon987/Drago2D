
config=debug

all:
	-$(MAKE) -C sandbox clean
	$(MAKE) -C sandbox -j16 config=$(config)

build:
	$(MAKE) -C sandbox -j16 config=$(config)

clean:
	$(MAKE) -C sandbox clean