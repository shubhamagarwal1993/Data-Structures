EXE = testimage testscene
OBJS = png.o image.o rgbapixel.o scene.o testimage.o testscene.o 
 
COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

png.o : png.cpp png.h image.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

image.o : image.cpp image.h rgbapixel.cpp rgbapixel.h png.h image.h
	$(COMPILER) $(COMPILER_FLAGS) image.cpp

testimage.o : testimage.cpp rgbapixel.cpp rgbapixel.h image.h
	$(COMPILER) $(COMPILER_FLAGS) testimage.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp
	
testscene.o : testscene.cpp scene.h image.h 
	$(COMPILER) $(COMPILER_FLAGS) testscene.cpp

scene.o : scene.cpp scene.h png.h image.h rgbapixel.h 	
	$(COMPILER) $(COMPILER_OPTS) scene.cpp

clean :
	-rm -f *.o $(EXE)
