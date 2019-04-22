extern "C" {
#include "ficl.h"
}
#include "mqttHelper.h"

// #include "smallest.h"

/*
extern "C" void athSmallest(ficlVm *vm) {
    smallest *n = new smallest();

    ficlStackPushPointer(vm->dataStack, n);
}
*/
extern "C" void mqttInstance(ficlVm *vm) {
    mqttHelper *mqtt = mqttHelper::Instance();

    ficlStackPushPointer(vm->dataStack, mqtt);
}

// 
// stack: addr len mqtt
//
extern "C" void setClientId(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);
    int len = ficlStackPopInteger(vm->dataStack);
    char *id = (char *)ficlStackPopPointer(vm->dataStack);
    id[len] = '\0';

    mqtt->setClientID( id );

}

extern "C" void mqttDump(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);

    mqtt->dump();
}

// 
// stack: addr len mqtt
//
extern "C" void setMqttHost(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);
    int len = ficlStackPopInteger(vm->dataStack);
    char *host = (char *)ficlStackPopPointer(vm->dataStack);
    host[len] = '\0';

    mqtt->setHost( host );
}
// 
// stack: addr len mqtt
//
extern "C" void mqttSubscribe(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);
    int len = ficlStackPopInteger(vm->dataStack);
    char *topic = (char *)ficlStackPopPointer(vm->dataStack);
    topic[len] = '\0';

    mqtt->subscribe( topic );
}
// 
// stack: mqtt
//
extern "C" void mqttConnect(ficlVm *vm) {
    bool failFlag = true;
    int rc = -1;

    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);

    failFlag = mqtt->connect2MQTT() ;

    rc = ( failFlag ) ? -1 : 0;
    ficlStackPushInteger(vm->dataStack, rc);

}
// 
// stack: loop_type mqtt
//
extern "C" void mqttGo(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);
    int lt = ficlStackPopInteger(vm->dataStack);

    mqtt->go( (enum loopType) lt);
}

extern "C" void setDefaultCallback(ficlVm *vm) {
    bool failFlag = true;
    int rc = -1;

    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);

    failFlag = mqtt->setMsgCallback();

    rc = ( failFlag ) ? -1 : 0;
    ficlStackPushInteger(vm->dataStack, rc);
}
// 
// stack: msg len topic len mqtt
//
extern "C" void mqttPublish(ficlVm *vm) {
    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);

    int tLen = ficlStackPopInteger(vm->dataStack);
    char *topic = (char *)ficlStackPopPointer(vm->dataStack);
    topic[tLen] = '\0';

    int mLen = ficlStackPopInteger(vm->dataStack);
    char *msg = (char *)ficlStackPopPointer(vm->dataStack);
    msg[mLen] = '\0';

    mqtt->publish( topic, msg );

}

