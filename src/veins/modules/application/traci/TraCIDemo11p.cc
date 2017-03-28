//
// Copyright (C) 20017-Cristhian Iza <7d5791@gmail.com>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins/modules/application/traci/TraCIDemo11p.h"

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

const simsignalwrap_t TraCIDemo11p::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);
const double timeSlot = 0.000013;

Define_Module(TraCIDemo11p);

void TraCIDemo11p::initialize(int stage) {
    arrivalSignal = registerSignal("arrival");
    arrivalSignal1 = registerSignal("arrival1");

    // Initialize variables.
    //timeout = 0.5;
    timeoutEvent = new cMessage("timeoutEvent");



	BaseWaveApplLayer::initialize(stage);
	if (stage == 0) {
		mobility = TraCIMobilityAccess().get(getParentModule());
		traci = mobility->getCommandInterface();
		traciVehicle = mobility->getVehicleCommandInterface();
		annotations = AnnotationManagerAccess().getIfExists();
		ASSERT(annotations);



        receivedBeacons = 0;
        receivedData = 0;
        contador=0;

        WATCH(receivedBeacons);
        WATCH(receivedData);
        WATCH(contador);

        listNst.push_back(0);
        listN0t.push_back(0);
        listChannelOccupancy.push_back(0);
        listTimeWindow.push_back(0);

        junctionIds = mobility->getCommandInterface()->getJunctionIds();

        for (list<string>::iterator i = junctionIds.begin(); i != junctionIds.end(); ++i) {
            string jId = *i;
            Coord jPos = mobility->getCommandInterface()->junction(jId).getPosition();
            junctionMap[jId] = jPos;
        }

        //


		sentMessage = false;
		lastDroveAt = simTime();
		findHost()->subscribe(parkingStateChangedSignal, this);
		isParking = false;
		sendWhileParking = par("sendWhileParking").boolValue();

        idMsg=0;

         // configurable variables in omnetpp.ini
         counterThreshold = par("counterThreshold").longValue();
         indexOfAccidentNode = par("indexOfAccidentNode").longValue();
         randomRebroadcastDelay = par("randomRebroadcastDelay").doubleValue();
         waitingTime= par("waitingTime").doubleValue()/1000000;
         counterWarningMessages=0;
         distanceThreshold = par("distanceThreshold").doubleValue();
         ProbabilityThreshold = par("ProbabilityThreshold").doubleValue();
         slots = par("slots").longValue();
         tao = par("tao").doubleValue();

	}
}


TraCIDemo11p::TraCIDemo11p()
{
    timeoutEvent = nullptr;

}


TraCIDemo11p::~TraCIDemo11p()
{
    cancelAndDelete(timeoutEvent);
}


void TraCIDemo11p::onBeacon(WaveShortMessage* wsm) {
    receivedBeacons++;
    DBG << "Received beacon priority  " << wsm->getPriority() << " at " << simTime() << std::endl;
    DBG << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Beacon <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<std::endl;

    int b=int(wsm->getCarId());
    double dsr=(mobility->getPositionAt(simTime()).distance(wsm->getSenderPos()));

    if (ListBeacon.SearchBeacon(b)){
            ListBeacon.UpdateBeacon(wsm->getCarId(),wsm->getArrivalTime(), wsm->getCreationTime(), wsm->getCarId(),wsm->getSpeed(), wsm->getVecX(),
                    wsm->getVecY(), wsm->getVecZ(), calcDistJoin(wsm),dsr, wsm->getTimeIdleChannel(),calcAbe(wsm), wsm->getAngleRad());
    }

    else{
            ListBeacon.AddBeacon(wsm->getCarId(),wsm->getArrivalTime(),  wsm->getCreationTime(), wsm->getCarId(),wsm->getSpeed(), wsm->getVecX(), wsm->getVecY(), wsm->getVecZ(),calcDistJoin(wsm), dsr,wsm->getTimeIdleChannel(),calcAbe(wsm),wsm->getAngleRad());
    }

    DBG << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Neighbors Table<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< "<<std::endl;
    double ttl=5;
    contador=ListBeacon.PurgeBeacons(ttl);
    ListBeacon.SortBeacons();
    ListBeacon.PrintBeacons();

}

void TraCIDemo11p::onData(WaveShortMessage* wsm) {
    findHost()->getDisplayString().updateWith("r=20,green");
    annotations->scheduleErase(1, annotations->drawLine(wsm->getSenderPos(), mobility->getPositionAt(simTime()), "blue"));

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage) sendMessage(wsm->getWsmData());

}


void TraCIDemo11p::sendMessage(std::string blockedRoadId) {
    sentMessage = true;

    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1,2);
    wsm->setWsmData(blockedRoadId.c_str());
    // Update Position

    wsm->setVecX(mobility->getPositionAt(simTime()).x);
    wsm->setVecY(mobility->getPositionAt(simTime()).y);
    wsm->setVecZ(mobility->getPositionAt(simTime()).z);

    wsm->setCarId(getParentModule()->getIndex());

    sendWSM(wsm);
}
void TraCIDemo11p::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
    else if (signalID == parkingStateChangedSignal) {
        handleParkingUpdate(obj);
    }
}

void TraCIDemo11p::handleParkingUpdate(cObject* obj) {
	isParking = mobility->getParkingState();
	if (sendWhileParking == false) {
		if (isParking == true) {
			(FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
		}
		else {
			Coord pos = mobility->getCurrentPosition();
			(FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
		}
	}
}
void TraCIDemo11p::handlePositionUpdate(cObject* obj) {
	BaseWaveApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10) {
            findHost()->getDisplayString().updateWith("r=16,red");
            //&& indexOfAccidentNode == getParentModule()->getIndex()
            if (!sentMessage && indexOfAccidentNode == getParentModule()->getIndex()){
                DBG << ">>>>>>>>>>>>>> NEW MESSAGE EMERGENCY GENERATED <<<<<<<<<<<<<"<<std::endl;
                std::cerr << "[INFO] ACCIDENT STARTED @simTime: " << simTime().str() << " for node: " << getParentModule()->getIndex() << endl;
                sendMessage(mobility->getRoadId());

            }
        }
    }
	else {
		lastDroveAt = simTime();
	}
}
void TraCIDemo11p::sendWSM(WaveShortMessage* wsm) {
	if (isParking && !sendWhileParking) return;
	sendDelayedDown(wsm,individualOffset);
}
void TraCIDemo11p::handleSelfMsg(cMessage *msg)
{

    // for "data" and "beacon" self messages
    if ((!strcmp(msg->getName(), "timeoutEvent"))) {
        forwardMessage(ProbabilityThreshold);
        return;

    }else{
        BaseWaveApplLayer::handleSelfMsg(msg);
        return;
    }
}
void TraCIDemo11p::forwardMessage(double p)
{
/*
    // if the number of times a warning message is received exceeds the counterThreshold
    // configuration variable, do not rebroadcast.*/
    //if (uniform(0,1) > p)
    if ( uniform(0,1) > p)
           {
           DBG << "Size of received messages is over the counterThreshold. No BROADCAST "<<std::endl;
           EV<<"CANCELANDO  SELFMSG1"<<endl;
          // cancelEvent(timeoutEvent);
           return;
          }


    EV<<"<< BROADCAST>>"<<endl;

    // Duplicate message and send the copy.
    WaveShortMessage *copy = receivedMessages[idMsg][0]->dup();

    // Increment hop count.
    copy->setHopCount(copy->getHopCount()+1);

    // Update Position

    copy->setVecX(mobility->getPositionAt(simTime()).x);
    copy->setVecY(mobility->getPositionAt(simTime()).y);
    copy->setVecZ(mobility->getPositionAt(simTime()).z);

    copy->setCarId(getParentModule()->getIndex());

    sendWSM(copy);

    // add the new message to storage fowardedMessages
    fowardedMessages[copy->getTreeId()].push_back(copy->dup());

    std::cerr << "[INFO] RE-BROADCAST  STARTED @simTime: " << simTime().str() << " from node: " << getParentModule()->getIndex() << endl;


    return;
}
bool TraCIDemo11p::hostIsClosestToJunction(string junctionId)
{
    // check to see if this host is near an intersection

    Coord jPos = junctionMap[junctionId];

    double hDist = jPos.distance(mobility->getPositionAt(simTime()));

    for (uint i = 0; i < neighbors.size(); ++i) {
        WaveShortMessage* neighbor = neighbors[i];
        if (jPos.distance(neighbor->getSenderPos()) < hDist) {
            return false;
        }
    }
    return true;
}


bool TraCIDemo11p::vehicleOnJunction()
{
    bool onJunction=false;
    // check to see if this host is near an intersection

    for (map<string,Coord>::iterator i = junctionMap.begin(); i != junctionMap.end(); ++i) {
        string jId = i->first;
        Coord jPos = i->second;
        Coord hPos = mobility->getPositionAt(simTime());
        if (jPos.distance(hPos) < 4) {
            onJunction=true;
            return onJunction;
        }
    }

    return onJunction;
}


string TraCIDemo11p::getIdJunction()
{
    // check to see if this host is near an intersection

    for (map<string,Coord>::iterator i = junctionMap.begin(); i != junctionMap.end(); ++i) {
        string jId = i->first;
        Coord jPos = i->second;
        Coord hPos = mobility->getPositionAt(simTime());
        if (jPos.distance(hPos) < 4) {
            return jId;
        }
    }

    return string();
}

double TraCIDemo11p::getMin(std::map<std::string, double> mymap)
{
  std::pair<std::string, double> min
      = *min_element(mymap.begin(), mymap.end(), CompareSecond());
  return min.second;
}




double TraCIDemo11p::calcAbe(WaveShortMessage* wsm)
{
    TraCIMobility* mySpeed = FindModule<TraCIMobility*>::findSubModule(getParentModule());
    Mac1609_4* myMacp = FindModule<Mac1609_4*>::findSubModule(getParentModule());
    string myroad=mobility->getRoadId();

    list<string> junctionIds = mobility->getCommandInterface()->getJunctionIds();

    double k=(((2 * (SLOTLENGTH_11P + SIFS_11P).dbl())+(double(myMacp->gethNumBackoff())*SLOTLENGTH_11P.dbl()))/par("beaconInterval").doubleValue());

    double f_m_N_s=-7.47*10e-5 *par("headerLength").doubleValue()-8.98*10e-3*double(ListBeacon.CounterBeacons())-1.42*10e-3*double(mySpeed->getSpeed())+1.98;
    f_m_N_s>1 ? f_m_N_s=0:f_m_N_s;

    double ts=wsm->getTimeIdleChannel().dbl();
    double tr=(simTime().dbl()-myMacp->getTotalBusyTime().dbl())/simTime().dbl();
    double myBitrate=((DeciderResult80211*)((PhyToMacControlInfo*)wsm->getControlInfo())->getDeciderResult())->getBitrate();
    double  abe1=double((1-k)*(1-f_m_N_s)*ts*tr*myBitrate);
    return abe1;
}
double TraCIDemo11p::calcDistJoin(WaveShortMessage* wsm)
{
    string jId = getIdJunction();
     DBG  << "JUNCTIONS" << std::endl;

     DBG  << jId << std::endl;


     for (list<string>::iterator i = junctionIds.begin(); i != junctionIds.end(); ++i) {
                    string jId = *i;
                    Coord jPos = mobility->getCommandInterface()->junction(jId).getPosition();
                    Coord hPos = mobility->getPositionAt(simTime());
                    junctionDistance[jId] = jPos.distance(hPos);
                }
     double distJ=getMin(junctionDistance);

     if (distJ>5){
             DBG  << "NO Junctions" << std::endl;
         }
     if (distJ<=5) {
             DBG  << "Junctions :" <<distJ<<" m."<<std::endl;
         }

     return distJ;

}



