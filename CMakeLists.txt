cmake_minimum_required(VERSION 2.8.9)
project( ficl )

if( ARCH STREQUAL "linux")
    message("Set")
else()
    message("NOT Set")
endif()

execute_process( WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ./mkFiclPlatform.sh)
execute_process( WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/softcore COMMAND make)

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

set(FICL_PLUS_SOURCES ${FICL_BASE_SOURCES} athExtras.cpp)

message("${ARCH}")


find_library(MATH m)
find_library(DYN dl)
find_library(PTHREAD pthread)

find_library(MQTT mosquitto)
find_library(SQL sqlite3)
find_library(CURL curl)


# link_directories(/usr/local/lib)
# find_library(PLC plc)

# message( ${PLC})
message( ${DYN})
message( ${SQL})

add_executable( ficl ${FICL_BASE_SOURCES})
add_executable( ficl++ mqttHelper.cpp ${FICL_PLUS_SOURCES})

set( platform ${CMAKE_CURRENT_SOURCE_DIR}/mkFiclPlatform.sh)

# add_custom_command( TARGET ficl PRE_BUILD 
#    COMMAND ${platform}
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Platform details."
# )


# SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1 -DATH_OBJECTS=1" )
SET_TARGET_PROPERTIES( ficl PROPERTIES COMPILE_FLAGS "-DATH=1")
SET_TARGET_PROPERTIES( ficl++ PROPERTIES COMPILE_FLAGS "-DATH=1 -DATH_OBJECTS=1")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")

target_include_directories(ficl++ PRIVATE /usr/local/include)

target_link_libraries(ficl ${MATH} ${DYN} ${PTHREAD})
target_link_libraries(ficl++ ${MATH} ${DYN} ${PTHREAD} ${CURL} ${SQL} ${MQTT} ${PLC})
