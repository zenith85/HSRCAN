/*
 * CANBus.cc
 *
 *  Created on: Apr 9, 2021
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
    long Errors;
    long broadcasted_signal=0;
    long received=0;
    double delayvalue=0.000008;
protected:
    virtual void initialize() override;
    void handleMessage(cMessage *msg) override;
};

Define_Module(SimpCANBus);


void SimpCANBus::initialize()
{
    Errors=0;

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
    sprintf(buf, "rcvd: %ld BroadCasted: %ld Errors: %ld", received, broadcasted_signal,Errors);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);

    //              seed resetter
                //struct timeval tv;
                //gettimeofday(&tv,NULL);
               // unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;//find the microseconds for seeding srand()
                //unsigned long time_in_micros = 1000000000 * tv.tv_sec + tv.tv_usec;//find the microseconds for seeding srand()
                //srand(time_in_micros);



    //error generation
//    A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use the modulo of the returned value by the range span and add the initial value of the range:
//    v1 = rand() % 100;         // v1 in the range 0 to 99
//    v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
//    v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014
    int geterr=this->getParentModule()->par("BER");
    int E;
    if (geterr!=0)
    {
        E=rand()%geterr;
    }else
    {
        E=0;
    }

    if (E==(geterr/2))
    {
        Errors++;
        msg->setName("Error");
        delete(msg);

    }else
    {
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




}


