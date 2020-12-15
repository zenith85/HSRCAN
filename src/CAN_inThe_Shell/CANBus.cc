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


class CANBus: public cModule { //cSimplemodule is the base class and Node is the inherited class


protected:
    void initialize() override;
};


class SimpCANBus: public cSimpleModule
{
    int broadcasted_signal=0;
    int received=0;
    double delayvalue=0.03;
protected:
    virtual void initialize();
    void handleMessage(cMessage *msg) override;
};

Define_Module(SimpCANBus);


void SimpCANBus::initialize()
{
    // if the delay value is not identified, then it will be 0.03 otherwise it will take the value of the delay itself
    if (this->getParentModule()->par("Delay").doubleValue()!=0)
    {
        delayvalue=this->getParentModule()->par("Delay").doubleValue();

    }
    else
    {
        this->getParentModule()->par("Delay").setDoubleValue(delayvalue);
    }
}

void SimpCANBus::handleMessage(cMessage *msg) {

    //display message received for debugging issues
    //getParentModule()->bubble("message received");
    //bubble("message received");
    //appendix F manual omnet++
    char buf[40];
    sprintf(buf, "rcvd: %ld BroadCasted: %ld", received, broadcasted_signal);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);

    //error generation
    int geterr=this->getParentModule()->par("BER");
    int E;
    if (geterr!=0)
    {
        E=rand()%geterr;
    }else
    {
        E=0;
    }

    if (E==5)
    {
        msg->setName("Error");
    }

    //page 79 doc.omnetpp.org/omnetpp4/manual.pdf [broadcasting messages]
    received+=1;
    int k=this->gateCount()/2;
    int outGateBaseID=gateBaseId("SCANB_interface$o");
    for (int i=0; i<k;i++)
    {
        //send(i==k-1 ? msg : msg->dup(), outGateBaseID+i);
        sendDelayed(i==k-1 ? msg : msg->dup(),delayvalue, outGateBaseID+i);
        broadcasted_signal+=1;
    }
}


