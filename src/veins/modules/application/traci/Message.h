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

#ifndef Message_H_
#define Message_H_

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "veins/modules/application/traci/Message.h"

using namespace std;


class TblMessage {
private:
    typedef struct message {
            long idMsg=0;
            simtime_t timeRx=0;
            simtime_t timeTx=0;
            long idVehicle=0;
            int hop=0;
            double s=0;
            double pX=0;
            double pY=0;
            double pZ=0;
            double disJunction=0;
            double disToSource=0;
            double distFromPreviousNode=0;
            simtime_t idleTime=0;
            double abe=0;
            // self messages for timers
            cMessage *messageStartMsg;  ///< start of each beacon
            message* next;

    }* messagePtr;

    messagePtr head;
    messagePtr curr;
    messagePtr temp;

public:
    TblMessage();
    void AddMessage(long b_idMsg, simtime_t b_timeRx, simtime_t b_timeTx, long b_idVehicle, int b_hop, double b_s, double b_pX, double b_pY, double b_pZ,
            double b_disJunction, double b_disToSource, double b_distFromPreviousNode, simtime_t b_idleTime, double b_abe);
    void DeleteMessage(long b_idMsg);
    void PrintMessages();
    void PrintWarningMessages();
    void SortMessages();
    int PurgeMessage(double b_ttl);
    int CounterMessages();
    bool SearchMessage(long b_idMsg);
    void UpdateMessage(long b_idMsg, simtime_t b_timeRx, simtime_t b_timeTx, long b_idVehicle, int b_hop, double b_s, double b_pX, double b_pY, double b_pZ, double b_disJunction, double b_disToSource, double b_distFromPreviousNode, simtime_t b_idleTime, double b_abe);

};

#endif /* Message_H_ */
