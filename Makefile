OBJECTS= dictionary.o system.o fileaccess.o float.o double.o prefix.o search.o softcore.o stack.o tools.o vm.o primitives.o bit.o lzuncompress.o mingw32.o utility.o hash.o callback.o word.o extras.o
HEADERS= ficl.h ficlplatform/mingw32.h
#
# Flags for shared library
TARGET =  # -ansi -DFICL_ANSI  # riscos MOTO_CPU32 
SHFLAGS = # -fPIC
CFLAGS = -O2 -fomit-frame-pointer -s $(SHFLAGS) $(TARGET)
CC     = gcc
LIB    = ar cr
RANLIB = ranlib

MAJOR = 4
MINOR = 0.31

ficl: main.o $(HEADERS) libficl.a
	$(CC) main.o -o ficl -L. -lficl -lgdi32 -lm

lib: libficl.so.$(MAJOR).$(MINOR)

# static library build
libficl.a: $(OBJECTS)
	$(LIB) libficl.a $(OBJECTS)
	$(RANLIB) libficl.a

# shared library build
libficl.so.$(MAJOR).$(MINOR): $(OBJECTS)
	$(CC) -shared -Wl,-soname,libficl.so.$(MAJOR).$(MINOR) \
	-o libficl.so.$(MAJOR).$(MINOR) $(OBJECTS)
	ln -sf libficl.so.$(MAJOR).$(MINOR) libficl.so

main: main.o ficl.h sysdep.h libficl.so.$(MAJOR).$(MINOR)
	$(CC) main.o -o main -L. -lficl -lm
	ln -sf libficl.so.$(MAJOR).$(MINOR) libficl.so.$(MAJOR)

mingw32.o: ficlplatform/mingw32.c $(HEADERS)
	$(CC) $(CFLAGS) -c ficlplatform/mingw32.c

#
#       generic object code
#
.SUFFIXES: .cxx .cc .c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

.cxx.o:
	$(CPP) $(CPFLAGS) -c $*.cxx

.cc.o:
	$(CPP) $(CPFLAGS) -c $*.cc
#
#       generic cleanup code
#
clean:
	rm -f *.o *.a libficl.*
