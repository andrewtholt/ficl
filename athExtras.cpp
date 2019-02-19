extern "C" {
#include "ficl.h"
}

// #include "smallest.h"
#include "plcBase.h"
#include "plcDatabase.h"

#include "ioClass.h"
#include "ioHARest.h"

/*
extern "C" void athSmallest(ficlVm *vm) {
    smallest *n = new smallest();

    ficlStackPushPointer(vm->dataStack, n);
}
*/
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
// Stack: name len plc -- 
extern "C" void plcLd(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Ld( shortName );
}

// STack: plc -- sqlite3 *db
extern "C" void plcGetDb(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    sqlite3 *db = me->getDB();

    ficlStackPushPointer(vm->dataStack, db);
}
// Stack: plc -- addr len
extern "C" void plcGetHostname(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    const string hostName = me->getHost();

    ficlStackPushPointer(vm->dataStack, (char *)hostName.c_str());
    ficlStackPushInteger(vm->dataStack, (int) hostName.length());
}

// Stack: db hostname len type len --
extern "C" void plcMkio(ficlVm *vm) {

    int tLen = ficlStackPopInteger(vm->dataStack);
    char *ioType = (char *)ficlStackPopPointer(vm->dataStack);
    ioType[tLen] = '\0';

    int hLen = ficlStackPopInteger(vm->dataStack);
    char *hostname = (char *)ficlStackPopPointer(vm->dataStack);
    hostname[hLen] = '\0';

    sqlite3 *db = (sqlite3 *) ficlStackPopPointer(vm->dataStack);


    ioClass *io = nullptr ;
    if( !strcmp(ioType, (char *)"HA_REST")){
        io = new ioHARest(db, hostname);
    }
    ficlStackPushPointer(vm->dataStack, io);

}
// Stack: name len plc -- 
extern "C" void plcSetHostname(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    int hLen = ficlStackPopInteger(vm->dataStack);
    char *hostname = (char *)ficlStackPopPointer(vm->dataStack);
    hostname[hLen] = '\0';

    me->setHost(hostname);
}
// Stack: plc -- port
extern "C" void plcGetPort(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int portNum = me->getPort();

    ficlStackPushInteger(vm->dataStack, portNum);

}
// Stack: port plc --
extern "C" void plcSetPort(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    int portNum = ficlStackPopInteger(vm->dataStack);

    me->setPort ( portNum);
}
// Stack plc -- bool
extern "C" void plcGetTOS(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    bool f = me->getTOS();

    int v = (f) ? -1 : 0;

    ficlStackPushInteger(vm->dataStack, v);
}

extern "C" void plcInputScan(ficlVm *vm) {
    ioClass *io = (ioClass *)ficlStackPopPointer(vm->dataStack) ;

    io->inputScan();
}

extern "C" void plcOutputUpdate(ficlVm *vm) {
    ioClass *io = (ioClass *)ficlStackPopPointer(vm->dataStack) ;

    io->outputUpdate();
}

extern "C" void plcOut(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Out( shortName );
}

extern "C" void plcEnd(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    me->plcEnd(0);
}

extern "C" void plcOr(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Or( shortName );
}

extern "C" void plcAndNot(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Andn( shortName );
}

extern "C" void plcGetValue(ficlVm *vm) {
    static char scratch[255];
    memset(scratch, 255, 0);

    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    string result = me->getValue( shortName );

    strncpy(scratch, result.c_str(), result.length());

    ficlStackPushPointer(vm->dataStack, (void *)scratch);
    ficlStackPushPointer(vm->dataStack, (void *)result.length());

}
//
// Stack: value len name len plc-handle
//
extern "C" void plcSetValue(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    int vLen = ficlStackPopInteger(vm->dataStack);
    char *value = (char *)ficlStackPopPointer(vm->dataStack);
    value[vLen]='\0';

    bool result = me->setValue( shortName, value );

}

extern "C" void plcGetBooleanValue(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    bool v = me->getBoolValue( shortName );

    ficlStackPushInteger(vm->dataStack, v );
}
// 
// Stack: bool name len plc
//
extern "C" void plcSetBooleanValue(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    bool v = ficlStackPopInteger(vm->dataStack);

    me->setBoolValue( shortName, v );


}

extern "C" void plcPop(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    bool v = me->fromStack();

    ficlStackPushInteger(vm->dataStack, v );
}

extern "C" void plcDepth(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int d = me->stackSize();

    ficlStackPushInteger(vm->dataStack, d );
}

extern "C" void plcPush(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);
    bool v = ficlStackPopInteger(vm->dataStack);

    me->toStack( v );


}

extern "C" void plcLdr(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Ldr( shortName );
}

extern "C" void plcLdf(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Ldf( shortName );
}

extern "C" void plcLdn(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Ldn( shortName );
}

extern "C" void plcOrn(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Orn( shortName );
}

extern "C" void plcOrr(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Orr( shortName );
}

extern "C" void plcOrf(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Orf( shortName );
}

extern "C" void plcAnd(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->And( shortName );
}

extern "C" void plcAndr(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Andr( shortName );
}

extern "C" void plcAndf(ficlVm *vm) {
    plcDatabase *me = (plcDatabase *)ficlStackPopPointer(vm->dataStack);

    int sLen = ficlStackPopInteger(vm->dataStack);
    char *shortName = (char *)ficlStackPopPointer(vm->dataStack);
    shortName[sLen]='\0';

    me->Andf( shortName );
}

extern "C" void plcTimLd(ficlVm *vm) {
}

