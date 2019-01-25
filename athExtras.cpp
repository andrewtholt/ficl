extern "C" {
#include "ficl.h"
}

#include "smallest.h"
#include "plcBase.h"
#include "plcDatabase.h"

extern "C" void athSmallest(ficlVm *vm) {
    smallest *n = new smallest();

    ficlStackPushPointer(vm->dataStack, n);
}


