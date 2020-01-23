cxx=c++

cflags=-std=c++17 -Wall -Wextra -Wno-unknown-pragmas

# Run "pkg-config --static --libs glfw3" to see what libraries are needed for your system
# -lGL is for linux systems specifically
lib:=-L/usr/local/lib -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGL
includes:=-I/home/dragomir/dev/Drago2D/include/

obj:=main.o d2d.o

exe=./main

all: $(exe)
	@echo ------------------------
	@$(exe)

$(exe): $(obj)
	$(cxx) $(cflags) $^ -o $@ $(lib)

%.o: %.cpp
	$(cxx) $(includes) -c $(cflags) $^ -o $@

clean:
	rm $(exe) $(obj)