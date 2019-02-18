cmake_minimum_required(VERSION 2.8.9)
project( ficl )

if( ARCH STREQUAL "linux")
    message("Set")
else()
    message("NOT Set")
endif()

set(FICL_BASE_SOURCES 
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

message("${ARCH}")

find_library(MATH m)
find_library(DYN dl)
find_library(PTHREAD pthread)

add_executable( ficl ${FICL_BASE_SOURCES})
add_executable( ficl++ ${FICL_BASE_SOURCES})

set( platform ${CMAKE_CURRENT_SOURCE_DIR}/mkFiclPlatform.sh)

add_custom_command( TARGET ficl PRE_BUILD 
    COMMAND ${platform}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Platform details."
)


# SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1 -DATH_OBJECTS=1" )
# SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1")
SET_TARGET_PROPERTIES( ficl++ PROPERTIES COMPILE_FLAGS "-DATH=1 -DATH_OBJECTS=1")

target_link_libraries(ficl ${MATH} ${DYN} ${PTHREAD})
target_link_libraries(ficl++ ${MATH} ${DYN} ${PTHREAD})
