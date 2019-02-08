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

extern "C" void plcNew(ficlVm *vm) {
    int len = ficlStackPopInteger(vm->dataStack);
    char *tmp = (char *)ficlStackPopPointer(vm->dataStack);
    tmp[len]='\0';

    string dbName = tmp;
    plcDatabase *me = new plcDatabase( dbName );

    ficlStackPushPointer(vm->dataStack, me);
}

