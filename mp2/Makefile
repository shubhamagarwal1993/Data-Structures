COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

all : testimage testscene

testimage : testimage.o image.o png.o rgbapixel.o
	$(LINKER) testimage.o image.o png.o rgbapixel.o -lpng -o testimage

testscene : testscene.o scene.o image.o png.o rgbapixel.o
	$(LINKER) testscene.o scene.o image.o png.o rgbapixel.o -lpng -o testscene

testimage.o: testimage.cpp image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) testimage.cpp

testscene.o: testscene.cpp scene.h image.h rgbapixel.h png.h
	$(COMPILER) $(COMPILER_FLAGS) testscene.cpp

scene.o : scene.cpp image.h scene.h rgbapixel.h png.h
	$(COMPILER) $(COMPILER_FLAGS) scene.cpp

image.o :image.cpp rgbapixel.h png.h
	$(COMPILER) $(COMPILER_FLAGS)	image.cpp

png.o: png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS)   png.cpp

rgbapixel.o: rgbapixel.cpp rgbapixel.h 
	$(COMPILER) $(COMPILER_FLAGS)   rgbapixel.cpp

clean:
	-rm -f *.o testimage testscene

