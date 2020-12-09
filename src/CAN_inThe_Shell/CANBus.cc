/*
 * CANBus.cc
 *
 *  Created on: Dec 8, 2020
 *      Author: ibrah
 */




#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

int max_connections;


class CANBus: public cModule { //cSimplemodule is the base class and Node is the inherited class

protected:
    void initialize() override;
};


class SimpCANBus: public cSimpleModule
{
    int broadcasted_signal=0;
    int received=0;
protected:
    void handleMessage(cMessage *msg) override;
};

Define_Module(SimpCANBus);


void SimpCANBus::handleMessage(cMessage *msg) {

    //display message received for debugging issues
    //getParentModule()->bubble("message received");
    //bubble("message received");
    //appendix F manual omnet++
    char buf[40];
    sprintf(buf, "rcvd: %ld BroadCasted: %ld", broadcasted_signal, received);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);

    //page 79 doc.omnetpp.org/omnetpp4/manual.pdf [broadcasting messages]
    received+=1;

    max_connections=this->getParentModule()->par("CON_NUM").intValue();
    int k=max_connections;
    int outGateBaseID=gateBaseId("SCANB_interface$o");
    for (int i=0; i<k;i++)
    {
        send(i==k-1 ? msg : msg->dup(), outGateBaseID+i);
        broadcasted_signal+=1;
    }
}


