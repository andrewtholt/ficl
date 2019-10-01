
#ifdef __cplusplus
extern "C" {
#pragma once
// #include "ficl.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#endif

#ifdef __cplusplus
}
#endif

class timerClass {
    private:
        uint64_t startTime=0;
        int started=0;
    public:
        timerClass();
        void startTimer(void);
        uint64_t readTimer(); // Return time elapsed in ms
        int getStarted();
};


