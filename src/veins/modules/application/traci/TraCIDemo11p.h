//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
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

#ifndef TraCIDemo11p_H
#define TraCIDemo11p_H

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"


#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
#include "veins/modules/mac/ieee80211p/Mac80211pToPhy11pInterface.h"
#include "veins/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h"


#include "veins/modules/phy/Decider80211p.h"
#include "veins/modules/phy/DeciderResult80211.h"
#include "veins/modules/phy/Decider80211pToPhy80211pInterface.h"
#include "veins/modules/phy/PhyLayer80211p.h"
#include "veins/modules/phy/NistErrorRate.h"
#include "veins/base/phyLayer/ChannelState.h"
#include "veins/modules/phy/SNRThresholdDecider.h"
#include "veins/base/utils/MacToNetwControlInfo.h"
#include "veins/base/phyLayer/BasePhyLayer.h"

#include "veins/base/phyLayer/PhyToMacControlInfo.h"
#include "veins/modules/phy/DeciderResult80211.h"
#include "veins/modules/utility/ConstsPhy.h"
#include "veins/modules/application/traci/beacon.h"
#include "veins/modules/application/traci/Message.h"

#include <string>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
using Veins::AnnotationManager;


#define SCHEDULED_REBROADCAST
typedef std::vector<WaveShortMessage*> WaveShortMessages;
typedef std::pair<std::string, double> MyPairType;
using std::vector;
using std::map;
typedef std::vector<WaveShortMessage*> WaveShortMessages;

typedef std::map<long,WaveShortMessages> MessagesTable;
typedef std::map<long, vector<simtime_t> > forwardingSlottedProbability;
//updated weights
typedef std::map<simtime_t, double> vectorMetrics;
typedef std::vector<double> updatedWeightsMetrics;



/**
 * Small IVC Demo using 11p
 */
class TraCIDemo11p : public BaseWaveApplLayer {
	public:
        struct CompareSecond
        {
            bool operator()(const MyPairType& left, const MyPairType& right) const
            {
            return left.second < right.second;
            }
        };
		virtual void initialize(int stage);
		virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);
		TraCIDemo11p();
        virtual ~TraCIDemo11p();
	protected:
		TraCIMobility* mobility;
		TraCICommandInterface* traci;
		TraCICommandInterface::Vehicle* traciVehicle;
		AnnotationManager* annotations;
		simtime_t lastDroveAt;
		bool sentMessage;
		bool isParking;
		bool sendWhileParking;
		static const simsignalwrap_t parkingStateChangedSignal;


	    /**********************************************/
	        long counterThreshold;
	        double distanceThreshold;
	        double ProbabilityThreshold;

	        long indexOfAccidentNode;
	        double randomRebroadcastDelay;
	        double waitingTime;
	        long idMsg;
	      //  map<long,WaveShortMessages> receivedMessages; //<-   // treeId, WSM vector
	        MessagesTable receivedMessages;
	        MessagesTable sendMessages;    // treeId, WSM vector
	        MessagesTable fowardedMessages; /// treeId, WSM vector<-----

	        map<simtime_t,long> receivedMessagesLogs;

	        TblMessage receivedMessagesTable;
	        forwardingSlottedProbability mapForwardingSlottedProbability;
	        long counterWarningMessages;
	        long slots;




		uint32_t receivedBeacons;
		uint32_t receivedData;
		BeaconList ListBeacon;
		int contador;

		std::list<int> listNst;
		std::list<int> listN0t;

		std::list<simtime_t> listChannelOccupancy;
		std::list<simtime_t> listTimeWindow;

		std::list<std::string> junctionIds;
		std::map<std::string,Coord> junctionMap;
		std::map<std::string,double> junctionDistance;
		std::map<long,WaveShortMessages> receivedMessageMap;
		std::vector<WaveShortMessage*> neighbors;
		vector<WaveShortMessage*> warningMessages;

		//updated weights
		vectorMetrics distanceFactor;
		vectorMetrics linkQualityFactor;
		updatedWeightsMetrics r;
		updatedWeightsMetrics r1;
		updatedWeightsMetrics r2;
		updatedWeightsMetrics uwp1;
		updatedWeightsMetrics uwp2;
		updatedWeightsMetrics p;

		//backoff
		vector<simtime_t> wt;



    private:
        simsignal_t arrivalSignal;
        simsignal_t arrivalSignal1;

        simtime_t timeout;  // timeout
        cMessage *timeoutEvent;  // holds pointer to the timeout self-message1

        simtime_t timeout2;  // timeout
        cMessage *timeoutEvent2;  // holds pointer to the timeout self-message2


        double tao;
        /*********************************************************************************************/


	protected:
		virtual void onBeacon(WaveShortMessage* wsm);
		virtual void onData(WaveShortMessage* wsm);
		virtual void sendMessage(std::string blockedRoadId);
		virtual void handlePositionUpdate(cObject* obj);
		virtual void handleParkingUpdate(cObject* obj);
		virtual void sendWSM(WaveShortMessage* wsm);
		virtual void handleSelfMsg(cMessage *msg);

		virtual void forwardMessage(double p);
        bool hostIsClosestToJunction(std::string junctionId);
        double  getMin(std::map<std::string, double> mymap);
        double calcAbe(WaveShortMessage* wsm);
        double calcDistJoin(WaveShortMessage* wsm);



        bool vehicleOnJunction();
        std::string getIdJunction();



};

#endif
