
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "veins/modules/application/traci/Message.h"
#include <iomanip>
#include <string>
using namespace std;

TblMessage::TblMessage(){
    head=NULL;
    curr=NULL;
    temp=NULL;
}

void TblMessage::AddMessage(long b_idMsg, simtime_t b_timeRx, simtime_t b_timeTx, long b_idVehicle, int b_hop, double b_s, double b_pX, double b_pY, double b_pZ,
            double b_disJunction, double b_disToSource, double b_distFromPreviousNode, simtime_t b_idleTime, double b_abe){
    messagePtr n = new message;
    n->next =NULL;
    n->idMsg=b_idMsg;
    n->timeTx=b_timeTx;
    n->timeRx=b_timeRx;
    n->idVehicle=b_idVehicle;
    n->hop=b_hop;
    n->s=b_s;
    n->pX=b_pX;
    n->pY=b_pY;
    n->pZ=b_pZ;
    n->disJunction=b_disJunction;
    n->disToSource=b_disToSource,
    n->distFromPreviousNode=b_distFromPreviousNode;
    n->idleTime=b_idleTime;
    n->abe=b_abe;



    if(head != NULL){
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;

        }
        curr->next=n;
    }
    else{
        head=n;
    }
}

void TblMessage::DeleteMessage(long delb_idVehicle){
    messagePtr delPtr = NULL;
    temp = head;
    curr = head;
    while(curr !=NULL && curr->idVehicle != delb_idVehicle){
        temp = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        EV << delb_idVehicle << " was not in the message List" <<std::endl;
        delete delPtr;
    }
    else{
        delPtr = curr;
        curr = curr->next;
        temp->next = curr;
        if(delPtr==head){
            head= head->next;
            temp = NULL;
        }


        delete delPtr;
        EV << delb_idVehicle << " This message was deleted" <<std::endl;
    }

}

void TblMessage::PrintMessages(){
    curr = head;
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    EV<<setw(40)<<"Message Table"<<endl;
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    EV<<"ID_Msg"<<setw(20)<<"ArrivalTime"<<setw(25)<<"SourceTxTime"<<setw(15)<<"SenderAddress"<<setw(15)<<"Delay"<<setw(15)<<"Hops"<<endl;
    while(curr != NULL)
    {
        EV<<curr->idMsg<<setw(25)<<curr->timeRx<<setw(20)<<curr->timeTx<<setw(15)<<curr->idVehicle<<setw(20)<<curr->timeRx-curr->timeTx<<setw(15)<<curr->hop<<endl;
        curr = curr->next;

    }
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

}


void TblMessage::PrintWarningMessages(){
    curr = head;
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    EV<<setw(40)<<"Warning Message Table"<<endl;
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    EV<<"ID_Msg"<<setw(20)<<"ArrivalTime"<<setw(25)<<"SourceTxTime"<<setw(15)<<"SenderAddress"<<setw(15)<<"Delay"<<setw(15)<<"Hops"<<setw(25)<<"DistanceToSource"<<setw(25)<<"DistanceFromPreviousNode"<<endl;
    while(curr != NULL)
    {
        EV<<curr->idMsg<<setw(25)<<curr->timeRx<<setw(20)<<curr->timeTx<<setw(15)<<curr->idVehicle<<setw(20)<<curr->timeRx-curr->timeTx<<setw(15)<<curr->hop<<setw(15)<<curr->disToSource<<setw(15)<<curr->distFromPreviousNode<<setw(2)<<"["<<curr->idVehicle<<"]"<<endl;
        curr = curr->next;

    }
    EV<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

}


int TblMessage::CounterMessages(){
    curr = head;
    int counter =0;

    while(curr != NULL)
    {
        curr = curr->next;
        counter++;


    }
    return counter;
}

bool TblMessage::SearchMessage(long delb_idVehicle){
    bool foundMessage;
    messagePtr delPtr = NULL;
    temp = head;
    curr = head;
    while(curr !=NULL && curr->idVehicle != delb_idVehicle){
        temp = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        EV << delb_idVehicle << " was not in the message List" <<std::endl;
        foundMessage = false;
    }
    else{
        EV << delb_idVehicle << " This message was found!!" <<std::endl;
        foundMessage = true;
    }
    delete delPtr;
    return foundMessage;

}


void TblMessage::UpdateMessage(long b_idMsg, simtime_t b_timeRx, simtime_t b_timeTx, long b_idVehicle, int b_hop, double b_s, double b_pX, double b_pY, double b_pZ,
        double b_disJunction, double b_disToSource, double b_distFromPreviousNode, simtime_t b_idleTime, double b_abe){
    messagePtr n = new message;
    n =head;

    while(n != NULL)
    {

        if(n->idVehicle == b_idVehicle)
        {
            n->idMsg=b_idMsg;
            n->timeTx=b_timeTx;
            n->timeRx=b_timeRx;
            n->idVehicle=b_idVehicle;
            n->hop=b_hop;
            n->s=b_s;
            n->pX=b_pX;
            n->pY=b_pY;
            n->pZ=b_pZ;
            n->disJunction=b_disJunction;
            n->disToSource=b_disToSource,
            n->idleTime= b_idleTime;
            n->abe=b_abe;
            return;
        }
        else
            n = n->next;

    }

}



void TblMessage::SortMessages(){
    bool changeMade;
    do{
        changeMade = false;
        curr = head;
        while( curr != NULL ){
            temp = curr;
            curr = curr->next;

            if( curr && curr->timeTx < temp->timeTx ){
                changeMade = true;
                swap( temp->timeTx, curr->timeTx );
                swap( temp->idVehicle, curr->idVehicle);
                swap( temp ->hop, curr->hop);
                swap( temp->s, curr->s);
                swap( temp->pX, curr->pX);
                swap( temp->pY, curr->pY);
                swap( temp->disToSource, curr->disToSource);
                swap( temp->idleTime, curr->idleTime);
                swap( temp->abe, curr->abe);
            }
        }
    } while( changeMade );
}



int TblMessage::PurgeMessage(double b_ttl){

    curr =head;
    double counter=0;
    double ttl=simTime().dbl();
    while(curr != NULL && curr->next !=NULL)
       {
           if(curr->next->timeTx < ttl-b_ttl)
           {
              temp = curr->next;
              curr->next= temp->next;
              free(temp);
              counter++;
           }
           else
               curr= curr->next;

       }

      EV  << " This message list was purged. "<<counter<<" has been deleted" <<std::endl;
      return counter;

}




