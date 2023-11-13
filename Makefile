
SOURCEDIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SOURCES   := $(shell find $(SOURCEDIR) -name '*.cpp')

clean:
	-[ -e build/out ] && rm -f build/out
	-[ -e out ] && rm -f out
build:
	mkdir -p build
	make -B clean
	g++ -o build/out -I./src $(SOURCES)
	cp build/out .