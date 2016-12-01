/*
*/
#define WIN32_LEAN_AND_MEAN	(1)
#include <windows.h>

#define FICL_WANT_PLATFORM (1)

#define FICL_PLATFORM_OS             "Mingw32"
#define FICL_PLATFORM_ARCHITECTURE   "x86"

#define FICL_PLATFORM_BASIC_TYPES    (1)
#define FICL_PLATFORM_ALIGNMENT      (4)
#define FICL_PLATFORM_INLINE	     __inline

#define FICL_PLATFORM_HAS_2INTEGER   (1)
#define FICL_PLATFORM_HAS_FTRUNCATE  (1)

#define fstat       _fstat
#define stat        _stat
#define getcwd      _getcwd
#define chdir       _chdir


extern int ftruncate(int fileno, size_t size);

typedef char ficlInteger8;
typedef unsigned char ficlUnsigned8;
typedef short ficlInteger16;
typedef unsigned short ficlUnsigned16;
typedef long ficlInteger32;
typedef unsigned long ficlUnsigned32;
typedef long long ficlInteger64;
typedef unsigned long long ficlUnsigned64;

typedef ficlInteger32 ficlInteger;
typedef ficlUnsigned32 ficlUnsigned;
typedef float ficlFloat;

typedef ficlInteger64 ficl2Integer;
typedef ficlUnsigned64 ficl2Unsigned;
