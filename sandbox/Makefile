cxx=c++

cflags=-std=c++17 -Wall -I ./.. -L../bin/debug -ldrago2d

obj:=main.o

exe=./main

all: $(exe)
	@echo ------------------------
	@$(exe)

$(exe): $(obj)
	$(cxx) $(cflags) $^ -o $@

$.o: %.cpp
	$(cxx) -c $(cflags) $^ -o $@

clean:
	rm $(exe) $(obj)