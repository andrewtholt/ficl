extern "C" {
#include "ficl.h"
}
#include "mqttHelper.h"
#include <iostream>
#include <queue>

using namespace std;

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

    mqtt->setUserDataPointer( (void *)vm);
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

struct ficlMsg {
    string t;
    string p;
};

queue<ficlMsg> q;

extern "C" {
    static void ficlMessageCallback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {

        struct ficlMsg out;

        printf("Ficl callback\n");
        if(message->payloadlen) {
            cout << "Topic   " << message->topic << endl;
            cout << "Message " << (char *)message->payload << endl;
            cout << "================" << endl;
        }

        ficlVm *myVm = (ficlVm *)obj;

        ficlStackPushPointer(myVm->dataStack, message->topic);
        ficlStackPushInteger(myVm->dataStack, strlen(message->topic));

        out.t = message->topic;
        out.p = (char *)message->payload;

        q.push(out);

        cout << "Queue size " << q.size() << endl;

    }
}

extern "C" void setFiclCallback(ficlVm *vm) {
    bool failFlag = true;
    int rc = -1;

    mqttHelper *mqtt = (mqttHelper *)ficlStackPopPointer(vm->dataStack);

    failFlag = mqtt->setMsgCallback((void *)ficlMessageCallback);
}

extern "C" void mqttGetMsg(ficlVm *vm) {
    struct ficlMsg n;

    static char topic[255];
    static char payload[255];

    bzero(topic, sizeof(topic));
    bzero(payload, sizeof(payload));

    n = q.front();

    string tmpTopic  = n.t;
    string tmpPayload  = n.p;

    strncpy(topic, tmpTopic.c_str(), tmpTopic.length());
    strncpy(payload, tmpPayload.c_str(), tmpPayload.length());

    ficlStackPushPointer(vm->dataStack, payload);
    ficlStackPushInteger(vm->dataStack, tmpPayload.length());

    ficlStackPushPointer(vm->dataStack, topic);
    ficlStackPushInteger(vm->dataStack, tmpTopic.length());

    q.pop();

}

