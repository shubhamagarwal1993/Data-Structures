EXENAME = lab_gdb

COMPILER = g++
COMPILER_OPTS = -c -ggdb -O0 -w
LINKER = g++

MAIN_OBJS = main.o png.o rgbapixel.o blockpng.o
MAIN_DEPS = list.h list.cpp list_given.h list_given.cpp png.o rgbapixel.o blockpng.o main.cpp

EPNG_DEPS = rgbapixel.o png.h png.cpp
BPNG_DEPS = png.o blockpng.h blockpng.cpp
RGBAPIXEL_DEPS = png.h rgbapixel.h rgbapixel.cpp

CODE_CLN = *.o $(EXENAME)

IMAG_CLN = reverse*.png

all: $(EXENAME)

$(EXENAME) : main.o
	$(LINKER) $(MAIN_OBJS) -lpng -o $(EXENAME)

main.o : $(MAIN_DEPS)
	$(COMPILER) $(COMPILER_OPTS) main.cpp

png.o : $(EPNG_DEPS)
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : $(RGBAPIXEL_DEPS)
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

blockpng.o : $(BPNG_DEPS)
	$(COMPILER) $(COMPILER_OPTS) blockpng.cpp

clean:
	-rm -f $(CODE_CLN) $(IMAG_CLN)
