/*
 * CANBus.cc
 *
 *  Created on: Dec 8, 2020
 *      Author: ibrah
 */




#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <omnetpp.h>

using namespace omnetpp;


class CANtoHSR: public cModule { //cSimplemodule is the base class and Node is the inherited class


protected:
    void initialize() override;
};


class SimpCANtoHSR: public cSimpleModule
{
    long framesrcvd_if_A;
    long framesrcvd_if_B;

private:
    cMessage *event;
    cMessage *HSRmsg;
    double frame_counter=0;
    double frame_counter_received=0;
    double frame_counter_received_from_A=0;
    double frame_counter_received_from_B=0;
public:
    SimpCANtoHSR();
    virtual~SimpCANtoHSR();
protected:
    virtual void initialize() override;
    void handleMessage(cMessage *msg) override;
};

Define_Module(SimpCANtoHSR);
SimpCANtoHSR::SimpCANtoHSR()
{
    event=HSRmsg=NULL;
    HSRmsg=NULL;
}
SimpCANtoHSR::~SimpCANtoHSR()
{
    cancelAndDelete(event);
    delete HSRmsg;
}

void SimpCANtoHSR::initialize()
{
    frame_counter=0;
    frame_counter_received=0;
    char buf[40];
    framesrcvd_if_A=0;framesrcvd_if_B=0;
    sprintf(buf, "IF_A: %ld IF_B: %ld", framesrcvd_if_A, framesrcvd_if_B);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);
}

void SimpCANtoHSR::handleMessage(cMessage *msg) {
    HSRmsg=msg;
    if (strcmp(msg->getArrivalGate()->getName(), "CANside$i")==0)
    {
        frame_counter=frame_counter+1;
        HSRmsg->addPar("NodeID").setStringValue(getParentModule()->par("NodeID"));
        HSRmsg->addPar("SQ_NUM").setDoubleValue(frame_counter);
        send(HSRmsg->dup(), "HSRside_1$o");
        send(HSRmsg->dup(), "HSRside_2$o");
    }
    //execute code if we receive from first interface
    if ((strcmp(msg->getArrivalGate()->getName(), "HSRside_1$i")==0) and (strcmp(HSRmsg->par("NodeID"),getParentModule()->par("NodeID"))!=0))
    {
        //if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received_from_A)
        if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received)
        {
            frame_counter_received_from_A=HSRmsg->par("SQ_NUM").doubleValue();
            //send(HSRmsg->dup(), "HSRside_2$o"); //send from the other path remove for QR implementation

            if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received)
            {
                //frame_counter_received++;//we should make this counter equal to the frame sq number
                frame_counter_received=HSRmsg->par("SQ_NUM").doubleValue();
                framesrcvd_if_A=framesrcvd_if_A+1;
                send(HSRmsg->dup(), "CANside$o");
            }
        }else
        {
            //do nothing
            delete msg;
        }
    }
    //execute code if we receive from second interface
    if ((strcmp(msg->getArrivalGate()->getName(), "HSRside_2$i")==0) and (strcmp(HSRmsg->par("NodeID"),getParentModule()->par("NodeID"))!=0))
    {
        //if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received_from_B)
        if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received)
        {
            frame_counter_received_from_B=HSRmsg->par("SQ_NUM").doubleValue();
            //send(HSRmsg->dup(), "HSRside_1$o");//send this from the other side removed for QR implementation

            if (HSRmsg->par("SQ_NUM").doubleValue()>frame_counter_received)
            {
                //frame_counter_received++;
                frame_counter_received=HSRmsg->par("SQ_NUM").doubleValue();
                framesrcvd_if_B=framesrcvd_if_B+1;
                send(HSRmsg->dup(), "CANside$o");
            }
        }else
        {
            delete msg;
            //do nothing
        }
    }

    char buf[40];
    sprintf(buf, "IF_A: %ld --- IF_B: %ld", framesrcvd_if_A, framesrcvd_if_B);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);
}


