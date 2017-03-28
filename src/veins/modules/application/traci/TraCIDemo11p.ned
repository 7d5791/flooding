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

package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;

simple TraCIDemo11p extends BaseWaveApplLayer
{
    
      parameters:
        @signal[arrival](type="simtime_t");
        @statistic[delayFirstNewMessage](title="delayFirstNewMessage"; source="arrival"; record=vector,stats; interpolationmode=none);
        
        @signal[arrival1](type="long");
        @statistic[hopCount](title="hop count"; source="arrival1"; record=vector,stats; interpolationmode=none);
        
    @class(TraCIDemo11p);
    @display("i=block/app2");
    bool sendWhileParking  = default(false); //send messages when the car is parked
    
    //*****************************************/
    double distanceThreshold = default(250);
    double ProbabilityThreshold = default(0.5);
    int counterThreshold = default(1);
    volatile double randomRebroadcastDelay = default(uniform(0,500));
    volatile double waitingTime = default(uniform(1,11));  // Time slot
    int indexOfAccidentNode = default(0);
    double WAIT_TIME = default(0.002);
	double delta = default(0.0002);
	int  slots = default(4);
	double tao = default(0.002);
    //****************************************************************/
    
}
