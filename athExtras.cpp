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
// 
// Stack: addr len -- plc
// 
extern "C" void plcNew(ficlVm *vm) {
    int len = ficlStackPopInteger(vm->dataStack);
    char *tmp = (char *)ficlStackPopPointer(vm->dataStack);
    tmp[len]='\0';

    string dbName = tmp;
    plcDatabase *me = new plcDatabase( dbName );

    ficlStackPushPointer(vm->dataStack, me);
}
// 
// Stack: flag plc --
// 
extern "C" void plcSetup(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    int flag = ficlStackPopInteger(vm->dataStack);

    bool clean=( flag == 0 ) ? false: true ;

    me->dbSetup(clean);

}
// 
// Stack: plc --
// 
extern "C" void plcDump(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    me->plcDump();
}
// 
// Stack: flag plc --
// 
extern "C" void plcVerbose(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    int flag = ficlStackPopInteger(vm->dataStack);

    bool verbose = ( flag == 0 ) ? false: true ;

    me->setVerbose( verbose );
}
//
// Stack: shortName len topic len direction len class len plc -- failFlag
//
extern "C" void addIO(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int cLen = ficlStackPopInteger(vm->dataStack);
    char *plcClass = (char *)ficlStackPopPointer(vm->dataStack);
    plcClass[cLen] = '\0';

    int dLen = ficlStackPopInteger(vm->dataStack);
    char *direction = (char *)ficlStackPopPointer(vm->dataStack);
    direction[dLen] = '\0';

    int tLen = ficlStackPopInteger(vm->dataStack);
    char *topic = (char *)ficlStackPopPointer(vm->dataStack);
    topic[tLen] = '\0';

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    bool failFlag = me->addIOPoint( shortName, topic, direction, plcClass );
}
