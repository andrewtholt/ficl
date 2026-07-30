#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>


struct athTimer {
    uint64_t startTime;
} ;

struct athTimer *ath_mkTimer();

void ath_startTimer( struct athTimer *ptr);

uint64_t ath_readTimer ( struct athTimer *ptr);

