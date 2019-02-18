cmake_minimum_required(VERSION 2.8.9)
project( ficl )

set(ATH 1)


if( ARCH STREQUAL "linux")
    message("Set")
else()
    message("NOT Set")

endif()


message("${ARCH}")

find_library(MATH m)
find_library(DYN dl)
find_library(PTHREAD pthread)

add_executable( ficl 
    main.c
    dictionary.c 
    system.c 
    fileaccess.c 
    float.c 
    double.c 
    prefix.c 
    search.c 
    softcore.c 
    stack.c 
    tools.c 
    vm.c 
    primitives.c 
    bit.c 
    lzuncompress.c 
    ficlplatform/unix.c 
    utility.c 
    hash.c 
    callback.c 
    word.c 
    curterm.c 
    extras.c 
    bswap.c 
    ficlblas.c 
    mt19937ar.c 
    mt19937-64.c 
    athTimer.c
    )

# SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1 -DATH_OBJECTS=1" )
SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1")
target_link_libraries(ficl ${MATH} ${DYN} ${PTHREAD})
