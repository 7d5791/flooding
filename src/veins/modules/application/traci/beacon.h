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

#ifndef BEACON_H_
#define BEACON_H_

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "veins/modules/application/traci/beacon.h"

using namespace std;


class BeaconList {
private:
    typedef struct beacon {
            int idMsg;
            simtime_t time=0;
            simtime_t timeRx=0;
            int idVehicle;
            double s;
            double pX;
            double pY;
            double pZ;
            double disJunction;
            double disToSource;
            simtime_t idleTime=0;
            double abe=0;
            double angle=0;
            // self messages for timers
            cMessage *beaconStartMsg;  ///< start of each beacon
            beacon* next;

    }* beaconPtr;

    beaconPtr head;
    beaconPtr curr;
    beaconPtr temp;

public:
    BeaconList();
    void AddBeacon(int b_idMsg, simtime_t b_time, simtime_t b_timeRx, int b_idVehicle,double b_s, double b_pX, double b_pY, double b_pZ,
            double b_disJunction, double b_disToSource, simtime_t b_idleTime, double b_abe, double b_angle);
    void DeleteBeacon(int b_idMsg);
    void PrintBeacons();
    void SortBeacons();
    int PurgeBeacons(double b_ttl);
    int CounterBeacons();
    bool SearchBeacon(int b_idMsg);
    void UpdateBeacon(int b_idMsg, simtime_t b_time,simtime_t b_timeRx, int b_idVehicle,double b_s, double b_pX, double b_pY, double b_pZ,
            double b_disJunction,double b_disToSource, simtime_t b_idleTime, double b_abe, double b_angle);

};

#endif /* BEACON_H_ */
