#include <stddef.h>  // defines NULL
#include <stdio.h>
#include <mosquitto.h>

#include <iostream>
#include <set>
#include "mqttHelper.h"

// Global static pointer used to ensure a single instance of the class.

using namespace std;
static set<std::string> subscribers;

// static set<string> subscribers;
mqttHelper* mqttHelper::m_pInstance = NULL;

static void connect_callback(struct mosquitto *mosq, void *obj, int result) {
    int rc = 0;
    printf("Connect_callback %d\n", result);

    if(subscribers.size() > 0) {
        cout << "Subscribe to:" << endl;

        for(auto i : subscribers ) {
            cout << "  " + i << endl;
            rc  = mosquitto_subscribe(mosq, NULL, i.c_str(), 1);
        }
    } else {
        cout << "Nothing to subscribe to:" << endl;
    }
}

static void disconnect_callback(struct mosquitto *mosq, void *obj, int result) {
    fprintf(stderr, "Disonnect_callback %d\n", result);
}

static void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {    
    cout << "Message callback" <<endl;

    if(message->payloadlen) {
        cout << "Topic   " << message->topic << endl;
        cout << "Message " << (char *)message->payload << endl;
        cout << "================" << endl;
    }

}
//
// This function is called to create an instance of the class. 
// Calling the constructor publicly is not allowed. The constructor 
// is private and is only called by this Instance function.
//
mqttHelper* mqttHelper::Instance() {
    printf("Instance\n");

    // Only allow one instance of class to be generated.
    if (!m_pInstance) {
        m_pInstance = new mqttHelper;
    } else {
        printf("Exists\n");
    }

    return m_pInstance;
}

/***********************************************************************
 *  Method: mqttHelper::setClientID
 *  Params: std::string iam
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::setClientID(std::string iam) {
    clientId = iam;
}


/***********************************************************************
 *  Method: mqttHelper::getHost
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string mqttHelper::getHost() {
    return mqttHost;
}


/***********************************************************************
 *  Method: mqttHelper::setHost
 *  Params: std::string host
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::setHost(std::string host) {
    mqttHost = host;
}


/***********************************************************************
 *  Method: mqttHelper::setUserDataPointer
 *  Params: void *ptr
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::setUserDataPointer(void *ptr) {
    userData = ptr;
}


/***********************************************************************
 *  Method: mqttHelper::getPort
 *  Params: 
 * Returns: int
 * Effects: 
 ***********************************************************************/
int mqttHelper::getPort() {
    return mqttPort;
}


/***********************************************************************
 *  Method: mqttHelper::setPort
 *  Params: int p
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::setPort(int p) {
    mqttPort = p ;
}


/***********************************************************************
 *  Method: mqttHelper::connect2MQTT
 *  Params: 
 * Returns: bool
 * Effects: 
 ***********************************************************************/
bool mqttHelper::connect2MQTT() {
    bool failFlag=true;

    mosq = mosquitto_new(clientId.c_str(), true, (void *)userData);

    if(mosq) {
        failFlag = false;
    } else {
        return failFlag;
    }
    // 
    // setup callbacks.
    // and connect.
    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_disconnect_callback_set(mosq, disconnect_callback);
    //    mosquitto_message_callback_set(mosq, message_callback);

    if(mosquitto_connect(mosq, mqttHost.c_str(), mqttPort, keepalive)) {
        failFlag = true;
    } else {
        failFlag = false;
        connected = true;
    }
    return failFlag;

}


/***********************************************************************
 *  Method: mqttHelper::subscribe
 *  Params: std::string topic
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::subscribe(std::string topic) {
    subscribers.insert(topic);

    if(connected) {
        cout << "Subscribe to " + topic << endl;
    }

}


/***********************************************************************
 *  Method: mqttHelper::publish
 *  Params: std::string topic, std::string payload
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::publish(std::string topic, std::string payload) {
    int rc = mosquitto_publish( mosq,
                                NULL,
                                topic.c_str(),
                                payload.length(),
                                payload.c_str(),
                                1,
                                true);
}


/***********************************************************************
 *  Method: mqttHelper::dump
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void mqttHelper::dump() {
    cout << "Client ID          :" + clientId << endl;
    cout << "MQTT Host          :" + mqttHost << endl;
    cout << "     port          :" << mqttPort << endl;
    cout << "No of subsciptions :" << subscribers.size() << endl;

    if( subscribers.size() > 0) {
        for(auto i : subscribers ) {
            cout << "  " + i << endl;
        }
    }
    cout << endl;
}

void mqttHelper::go(enum loopType t) {
    int rc=0;
    if(connected) {
        switch(t) {
            case ONCE:
                rc = mosquitto_loop(mosq,100,1);
                break;
        }
    }
}

bool mqttHelper::setMsgCallback( ) {
    bool failFlag=true;

    if(mosq) {
        msgCb = message_callback;
        mosquitto_message_callback_set(mosq, msgCb);
    }
}

bool mqttHelper::setMsgCallback( void *fptr) {
    bool failFlag = true;

    if (mosq) {
        msgCb = (void (*)(mosquitto*, void*, const mosquitto_message*))fptr;
        mosquitto_message_callback_set(mosq, msgCb);
        failFlag = false;
    }
    return failFlag;
}

