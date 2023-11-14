
LDFLAGS   := -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr -lXi
SOURCEDIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SOURCES   := $(shell find $(SOURCEDIR) -name '*.cpp')

clean:
	-[ -e build/out ] && rm -f build/out
	-[ -e out ] && rm -f out
build:
	mkdir -p build
	make -B clean
	g++ -o build/out -I./src $(SOURCES) $(LDFLAGS) $(NDEBUG)
	cp build/out .
symbuild:
	mkdir -p build
	make -B clean
	g++ -g -o build/out -I./src $(SOURCES) $(LDFLAGS) $(NDEBUG)
	cp build/out .
run:
	make -B build
	./out $(ARGS)
memcheck:
	make -B symbuild NDEBUG="-DNDEBUG"
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./out $(ARGS)