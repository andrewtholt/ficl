#include "athTimer.h"

struct athTimer *mkTimer() {

    struct athTimer *ptr = calloc(1, sizeof(struct athTimer));

    return ptr;
}

void startTimer(struct athTimer *ptr) {
    struct timeval startTV;

    gettimeofday(&startTV, NULL);
    ptr->startTime = (startTV.tv_sec * 1000) + (startTV.tv_usec / 1000);
}

uint64_t readTimer(struct athTimer *ptr) {
    struct timeval nowTV;

    gettimeofday(&nowTV, NULL);

    uint64_t nowTime = (nowTV.tv_sec * 1000) + (nowTV.tv_usec / 1000);

    return( nowTime - ptr->startTime );

}
