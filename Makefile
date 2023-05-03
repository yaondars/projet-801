all: opencv_test.pgr

CC=clang++
CFLAGS=-Wall -O3
LDFLAGS=

CFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)

opencv_test.pgr: obj/opencv_simple.o obj/gaussianNoise.o obj/gauss_seidel.o
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)

obj/%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

proper :
	rm -f obj/*.o

clean:
	rm -rf obj/*.o *.pgr
