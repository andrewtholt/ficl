#ifdef __cplusplus
#include "plcDatabase.h"
#endif
void athSmallest(ficlVm *vm) ;

void mkTimerClass(ficlVm *vm) ;
void startTimer(ficlVm *vm);
void readTimer(ficlVm *vm);

void plcNew(ficlVm *vm) ;
void plcSetup(ficlVm *vm) ;
void plcDump(ficlVm *vm) ;
void plcVerbose(ficlVm *vm) ;
void addIO(ficlVm *vm);
void plcLd(ficlVm *vm);
void plcInputScan(ficlVm *vm);
void plcGetDb(ficlVm *vm);
void plcGetHostname(ficlVm *vm);
void plcMkio(ficlVm *vm);
void plcSetHostname(ficlVm *vm);
void plcGetPort(ficlVm *vm);
void plcSetPort(ficlVm *vm);
void plcGetTOS(ficlVm *vm);
void plcOutputUpdate(ficlVm *vm);
void plcOut(ficlVm *vm);
void plcEnd(ficlVm *vm);
void plcOr(ficlVm *vm);
void plcAndNot(ficlVm *vm);
void plcGetValue(ficlVm *vm);
void plcSetValue(ficlVm *vm);
void plcGetBooleanValue(ficlVm *vm);
void plcSetBooleanValue(ficlVm *vm);
void plcPop(ficlVm *vm);
void plcDepth(ficlVm *vm);
void plcPush(ficlVm *vm);
void plcLdr(ficlVm *vm);
void plcLdf(ficlVm *vm);
void plcLdn(ficlVm *vm);
void plcOrn(ficlVm *vm);
void plcOrr(ficlVm *vm);
void plcOrf(ficlVm *vm);
void plcAnd(ficlVm *vm);
void plcAndr(ficlVm *vm);
void plcAndf(ficlVm *vm);
void plcTimLd(ficlVm *vm);
void mqttInstance(ficlVm *vm);
void setClientId(ficlVm *vm);
void mqttDump(ficlVm *vm);
void setMqttHost(ficlVm *vm);
void mqttSubscribe(ficlVm *vm);
void mqttConnect(ficlVm *vm);
void mqttGo(ficlVm *vm);
void setDefaultCallback(ficlVm *vm);
void mqttPublish(ficlVm *vm);
void setFiclCallback(ficlVm *vm);

void mqttGetMsg(ficlVm *vm);
void msgCount(ficlVm *vm);
