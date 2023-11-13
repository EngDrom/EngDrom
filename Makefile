
LDFLAGS   := -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr -lXi
SOURCEDIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SOURCES   := $(shell find $(SOURCEDIR) -name '*.cpp')

clean:
	-[ -e build/out ] && rm -f build/out
	-[ -e out ] && rm -f out
build:
	mkdir -p build
	make -B clean
	g++ -o build/out -I./src $(SOURCES) $(LDFLAGS)
	cp build/out .
run:
	make -B build
	./out $(ARGS)
debug:
	mkdir -p build
	make -B clean
	g++ -g -fsanitize=address,undefined -o build/out -I./src $(SOURCES) $(LDFLAGS)
	cp build/out .