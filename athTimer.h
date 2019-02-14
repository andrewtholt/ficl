#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>


struct athTimer {
    uint64_t startTime;
} ;

struct athTimer *mkTimer();

void startTimer( struct athTimer *ptr);

uint64_t readTimer ( struct athTimer *ptr);

