cxx=c++

cflags:=-std=c++17 -Wall -Wextra

config=debug

dir:=$(CURDIR)

ifeq ($(config), debug)
	cflags:=$(cflags) -g
else ifeq ($(config), release)
	cflags:=$(cflags) -O3
else
	$(error config must be equal debug or release)
endif

src_dir:=$(dir)/src/
bin_dir:=$(dir)/bin/$(config)/
obj_dir:=$(bin_dir)int/

srcs:=$(wildcard $(src_dir)*.cpp)
obj:=$(subst $(src_dir), $(obj_dir), $(srcs))
obj:=$(obj:.cpp=.o)

bin_name:=libdrago2d.a

drago2d:=$(bin_dir)$(bin_name)

all: $(drago2d)
	@echo $(srcs)
	@echo $(obj)
	@echo $(src_dir)
	@echo $(obj_dir)


$(drago2d): $(obj)
	ar rs $@ $^

$(obj_dir)%.o: $(src_dir)%.cpp
	$(cxx) $(cflags) -c -o $@ $^

clean:
	rm $(drago2d) $(obj)