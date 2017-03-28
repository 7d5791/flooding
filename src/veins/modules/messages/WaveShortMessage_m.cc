//
// Generated file, do not edit! Created by nedtool 4.6 from veins/modules/messages/WaveShortMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WaveShortMessage_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(WaveShortMessage);

WaveShortMessage::WaveShortMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    this->wsmVersion_var = 0;
    this->securityType_var = 0;
    this->channelNumber_var = 0;
    this->dataRate_var = 1;
    this->priority_var = 3;
    this->psid_var = 0;
    this->psc_var = "Service with some Data";
    this->wsmLength_var = 0;
    this->wsmData_var = "Some Data";
    this->senderAddress_var = 0;
    this->recipientAddress_var = -1;
    this->serial_var = 0;
    this->timestamp_var = 0;
    this->speed_var = 0;
    this->angleRad_var = 0;
    this->vecX_var = 0;
    this->vecY_var = 0;
    this->vecZ_var = 0;
    this->carId_var = 0;
    this->timeIdleChannel_var = 0;
    this->hopCount_var = 1;
}

WaveShortMessage::WaveShortMessage(const WaveShortMessage& other) : ::cPacket(other)
{
    copy(other);
}

WaveShortMessage::~WaveShortMessage()
{
}

WaveShortMessage& WaveShortMessage::operator=(const WaveShortMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WaveShortMessage::copy(const WaveShortMessage& other)
{
    this->wsmVersion_var = other.wsmVersion_var;
    this->securityType_var = other.securityType_var;
    this->channelNumber_var = other.channelNumber_var;
    this->dataRate_var = other.dataRate_var;
    this->priority_var = other.priority_var;
    this->psid_var = other.psid_var;
    this->psc_var = other.psc_var;
    this->wsmLength_var = other.wsmLength_var;
    this->wsmData_var = other.wsmData_var;
    this->senderAddress_var = other.senderAddress_var;
    this->recipientAddress_var = other.recipientAddress_var;
    this->serial_var = other.serial_var;
    this->senderPos_var = other.senderPos_var;
    this->timestamp_var = other.timestamp_var;
    this->speed_var = other.speed_var;
    this->angleRad_var = other.angleRad_var;
    this->vecX_var = other.vecX_var;
    this->vecY_var = other.vecY_var;
    this->vecZ_var = other.vecZ_var;
    this->carId_var = other.carId_var;
    this->timeIdleChannel_var = other.timeIdleChannel_var;
    this->hopCount_var = other.hopCount_var;
}

void WaveShortMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->wsmVersion_var);
    doPacking(b,this->securityType_var);
    doPacking(b,this->channelNumber_var);
    doPacking(b,this->dataRate_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->psid_var);
    doPacking(b,this->psc_var);
    doPacking(b,this->wsmLength_var);
    doPacking(b,this->wsmData_var);
    doPacking(b,this->senderAddress_var);
    doPacking(b,this->recipientAddress_var);
    doPacking(b,this->serial_var);
    doPacking(b,this->senderPos_var);
    doPacking(b,this->timestamp_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->angleRad_var);
    doPacking(b,this->vecX_var);
    doPacking(b,this->vecY_var);
    doPacking(b,this->vecZ_var);
    doPacking(b,this->carId_var);
    doPacking(b,this->timeIdleChannel_var);
    doPacking(b,this->hopCount_var);
}

void WaveShortMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->wsmVersion_var);
    doUnpacking(b,this->securityType_var);
    doUnpacking(b,this->channelNumber_var);
    doUnpacking(b,this->dataRate_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->psid_var);
    doUnpacking(b,this->psc_var);
    doUnpacking(b,this->wsmLength_var);
    doUnpacking(b,this->wsmData_var);
    doUnpacking(b,this->senderAddress_var);
    doUnpacking(b,this->recipientAddress_var);
    doUnpacking(b,this->serial_var);
    doUnpacking(b,this->senderPos_var);
    doUnpacking(b,this->timestamp_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->angleRad_var);
    doUnpacking(b,this->vecX_var);
    doUnpacking(b,this->vecY_var);
    doUnpacking(b,this->vecZ_var);
    doUnpacking(b,this->carId_var);
    doUnpacking(b,this->timeIdleChannel_var);
    doUnpacking(b,this->hopCount_var);
}

int WaveShortMessage::getWsmVersion() const
{
    return wsmVersion_var;
}

void WaveShortMessage::setWsmVersion(int wsmVersion)
{
    this->wsmVersion_var = wsmVersion;
}

int WaveShortMessage::getSecurityType() const
{
    return securityType_var;
}

void WaveShortMessage::setSecurityType(int securityType)
{
    this->securityType_var = securityType;
}

int WaveShortMessage::getChannelNumber() const
{
    return channelNumber_var;
}

void WaveShortMessage::setChannelNumber(int channelNumber)
{
    this->channelNumber_var = channelNumber;
}

int WaveShortMessage::getDataRate() const
{
    return dataRate_var;
}

void WaveShortMessage::setDataRate(int dataRate)
{
    this->dataRate_var = dataRate;
}

int WaveShortMessage::getPriority() const
{
    return priority_var;
}

void WaveShortMessage::setPriority(int priority)
{
    this->priority_var = priority;
}

int WaveShortMessage::getPsid() const
{
    return psid_var;
}

void WaveShortMessage::setPsid(int psid)
{
    this->psid_var = psid;
}

const char * WaveShortMessage::getPsc() const
{
    return psc_var.c_str();
}

void WaveShortMessage::setPsc(const char * psc)
{
    this->psc_var = psc;
}

int WaveShortMessage::getWsmLength() const
{
    return wsmLength_var;
}

void WaveShortMessage::setWsmLength(int wsmLength)
{
    this->wsmLength_var = wsmLength;
}

const char * WaveShortMessage::getWsmData() const
{
    return wsmData_var.c_str();
}

void WaveShortMessage::setWsmData(const char * wsmData)
{
    this->wsmData_var = wsmData;
}

int WaveShortMessage::getSenderAddress() const
{
    return senderAddress_var;
}

void WaveShortMessage::setSenderAddress(int senderAddress)
{
    this->senderAddress_var = senderAddress;
}

int WaveShortMessage::getRecipientAddress() const
{
    return recipientAddress_var;
}

void WaveShortMessage::setRecipientAddress(int recipientAddress)
{
    this->recipientAddress_var = recipientAddress;
}

int WaveShortMessage::getSerial() const
{
    return serial_var;
}

void WaveShortMessage::setSerial(int serial)
{
    this->serial_var = serial;
}

Coord& WaveShortMessage::getSenderPos()
{
    return senderPos_var;
}

void WaveShortMessage::setSenderPos(const Coord& senderPos)
{
    this->senderPos_var = senderPos;
}

simtime_t WaveShortMessage::getTimestamp() const
{
    return timestamp_var;
}

void WaveShortMessage::setTimestamp(simtime_t timestamp)
{
    this->timestamp_var = timestamp;
}

double WaveShortMessage::getSpeed() const
{
    return speed_var;
}

void WaveShortMessage::setSpeed(double speed)
{
    this->speed_var = speed;
}

double WaveShortMessage::getAngleRad() const
{
    return angleRad_var;
}

void WaveShortMessage::setAngleRad(double angleRad)
{
    this->angleRad_var = angleRad;
}

double WaveShortMessage::getVecX() const
{
    return vecX_var;
}

void WaveShortMessage::setVecX(double vecX)
{
    this->vecX_var = vecX;
}

double WaveShortMessage::getVecY() const
{
    return vecY_var;
}

void WaveShortMessage::setVecY(double vecY)
{
    this->vecY_var = vecY;
}

double WaveShortMessage::getVecZ() const
{
    return vecZ_var;
}

void WaveShortMessage::setVecZ(double vecZ)
{
    this->vecZ_var = vecZ;
}

int WaveShortMessage::getCarId() const
{
    return carId_var;
}

void WaveShortMessage::setCarId(int carId)
{
    this->carId_var = carId;
}

simtime_t WaveShortMessage::getTimeIdleChannel() const
{
    return timeIdleChannel_var;
}

void WaveShortMessage::setTimeIdleChannel(simtime_t timeIdleChannel)
{
    this->timeIdleChannel_var = timeIdleChannel;
}

int WaveShortMessage::getHopCount() const
{
    return hopCount_var;
}

void WaveShortMessage::setHopCount(int hopCount)
{
    this->hopCount_var = hopCount;
}

class WaveShortMessageDescriptor : public cClassDescriptor
{
  public:
    WaveShortMessageDescriptor();
    virtual ~WaveShortMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(WaveShortMessageDescriptor);

WaveShortMessageDescriptor::WaveShortMessageDescriptor() : cClassDescriptor("WaveShortMessage", "cPacket")
{
}

WaveShortMessageDescriptor::~WaveShortMessageDescriptor()
{
}

bool WaveShortMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<WaveShortMessage *>(obj)!=NULL;
}

const char *WaveShortMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int WaveShortMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 22+basedesc->getFieldCount(object) : 22;
}

unsigned int WaveShortMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<22) ? fieldTypeFlags[field] : 0;
}

const char *WaveShortMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "wsmVersion",
        "securityType",
        "channelNumber",
        "dataRate",
        "priority",
        "psid",
        "psc",
        "wsmLength",
        "wsmData",
        "senderAddress",
        "recipientAddress",
        "serial",
        "senderPos",
        "timestamp",
        "speed",
        "angleRad",
        "vecX",
        "vecY",
        "vecZ",
        "carId",
        "timeIdleChannel",
        "hopCount",
    };
    return (field>=0 && field<22) ? fieldNames[field] : NULL;
}

int WaveShortMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmVersion")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "securityType")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataRate")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "psid")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "psc")==0) return base+6;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmLength")==0) return base+7;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmData")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "recipientAddress")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "serial")==0) return base+11;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+12;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+13;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+14;
    if (fieldName[0]=='a' && strcmp(fieldName, "angleRad")==0) return base+15;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecX")==0) return base+16;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecY")==0) return base+17;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecZ")==0) return base+18;
    if (fieldName[0]=='c' && strcmp(fieldName, "carId")==0) return base+19;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeIdleChannel")==0) return base+20;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+21;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *WaveShortMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "string",
        "int",
        "string",
        "int",
        "int",
        "int",
        "Coord",
        "simtime_t",
        "double",
        "double",
        "double",
        "double",
        "double",
        "int",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<22) ? fieldTypeStrings[field] : NULL;
}

const char *WaveShortMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int WaveShortMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WaveShortMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getWsmVersion());
        case 1: return long2string(pp->getSecurityType());
        case 2: return long2string(pp->getChannelNumber());
        case 3: return long2string(pp->getDataRate());
        case 4: return long2string(pp->getPriority());
        case 5: return long2string(pp->getPsid());
        case 6: return oppstring2string(pp->getPsc());
        case 7: return long2string(pp->getWsmLength());
        case 8: return oppstring2string(pp->getWsmData());
        case 9: return long2string(pp->getSenderAddress());
        case 10: return long2string(pp->getRecipientAddress());
        case 11: return long2string(pp->getSerial());
        case 12: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 13: return double2string(pp->getTimestamp());
        case 14: return double2string(pp->getSpeed());
        case 15: return double2string(pp->getAngleRad());
        case 16: return double2string(pp->getVecX());
        case 17: return double2string(pp->getVecY());
        case 18: return double2string(pp->getVecZ());
        case 19: return long2string(pp->getCarId());
        case 20: return double2string(pp->getTimeIdleChannel());
        case 21: return long2string(pp->getHopCount());
        default: return "";
    }
}

bool WaveShortMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setWsmVersion(string2long(value)); return true;
        case 1: pp->setSecurityType(string2long(value)); return true;
        case 2: pp->setChannelNumber(string2long(value)); return true;
        case 3: pp->setDataRate(string2long(value)); return true;
        case 4: pp->setPriority(string2long(value)); return true;
        case 5: pp->setPsid(string2long(value)); return true;
        case 6: pp->setPsc((value)); return true;
        case 7: pp->setWsmLength(string2long(value)); return true;
        case 8: pp->setWsmData((value)); return true;
        case 9: pp->setSenderAddress(string2long(value)); return true;
        case 10: pp->setRecipientAddress(string2long(value)); return true;
        case 11: pp->setSerial(string2long(value)); return true;
        case 13: pp->setTimestamp(string2double(value)); return true;
        case 14: pp->setSpeed(string2double(value)); return true;
        case 15: pp->setAngleRad(string2double(value)); return true;
        case 16: pp->setVecX(string2double(value)); return true;
        case 17: pp->setVecY(string2double(value)); return true;
        case 18: pp->setVecZ(string2double(value)); return true;
        case 19: pp->setCarId(string2long(value)); return true;
        case 20: pp->setTimeIdleChannel(string2double(value)); return true;
        case 21: pp->setHopCount(string2long(value)); return true;
        default: return false;
    }
}

const char *WaveShortMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 12: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *WaveShortMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    WaveShortMessage *pp = (WaveShortMessage *)object; (void)pp;
    switch (field) {
        case 12: return (void *)(&pp->getSenderPos()); break;
        default: return NULL;
    }
}


