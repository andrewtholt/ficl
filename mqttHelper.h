
#include <string>
#include <set>
#include <mosquitto.h>

enum loopType {
    INVALID=0,
    ONCE,
    BLOCK,
    BACK
};

class mqttHelper{

    private:
        mqttHelper(){};  // Private so that it can  not be called
        mqttHelper(mqttHelper const&){};             // copy constructor is private
        mqttHelper& operator=(mqttHelper const&){};  // assignment operator is private
        static mqttHelper* m_pInstance;

        std::string mqttHost = "localhost";
        int mqttPort = 1883 ;
        std::string clientId = "SET_ME";
        struct mosquitto *mosq;
        void *userData = NULL;
        int keepalive = 0;
        bool connected = false;

        void (*msgCb) (struct mosquitto *, void *, const mosquitto_message* );

    public:
        bool fred = false;
        static mqttHelper *Instance();

        void dump();
        void setClientID(std::string iam);

        std::string getHost();
        void setHost(std::string host);

        void setUserDataPointer(void *ptr);
        bool setMsgCallback( void *);
        bool setMsgCallback( );

        int getPort();
        void setPort(int p);

        bool connect2MQTT();

        void subscribe(std::string topic);
        void publish(std::string topic, std::string payload);

        void go(enum loopType t);
};

