/***********************************************************************
 * AUTHOR: andrewh <andrewh>
 *   FILE: .//timerClass.cpp
 *   DATE: Tue Oct  1 10:03:19 2019
 *  DESCR: 
 ***********************************************************************/
#include "timerClass.h"
#include <iostream>

/***********************************************************************
 *  Method: timerClass::timerClass
 *  Params: 
 * Effects: 
 ***********************************************************************/
timerClass::timerClass() {
    started = 0;
    std::cout << "Timer" << std::endl;
}

/***********************************************************************
 *  Method: timerClass::startTimer
 *  Params: void
 * Returns: void
 * Effects: 
 ***********************************************************************/
void timerClass::startTimer(void) {
    struct timeval startTV;
    gettimeofday(&startTV, NULL);
    startTime = (startTV.tv_sec * 1000) + (startTV.tv_usec / 1000);
    started = 1;
}


/***********************************************************************
 *  Method: timerClass::readTimer
 *  Params: 
 * Returns: uint64_t
 * Effects: 
 ***********************************************************************/
uint64_t timerClass::readTimer() {
    struct timeval nowTV;
    uint64_t result=0;

    if(started != 0) {
        gettimeofday(&nowTV, NULL);

        uint64_t nowTime = (nowTV.tv_sec * 1000) + (nowTV.tv_usec / 1000);

        result = nowTime - startTime ;
    } else {
        result=0;
    }
    return( result );
}


