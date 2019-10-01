#include <unistd.h>
#include "timerClass.h"
#include <iostream>

using namespace std;

int main() {

    timerClass *fred = new timerClass();

    fred->getStarted();
    sleep(1);
    cout << fred->readTimer() << endl;

    fred->startTimer();
    fred->getStarted();

    sleep(1);
    cout << fred->readTimer() << endl;

    sleep(1);
    cout << fred->readTimer() << endl;
}
