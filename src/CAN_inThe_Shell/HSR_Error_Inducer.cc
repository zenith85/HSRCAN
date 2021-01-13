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


//class HSR_Error_Inducer: public cSimpleModule { //cSimplemodule is the base class and Node is the inherited class
//
//
//protected:
//    void initialize() override;
//};


class HSR_Error_Inducer: public cSimpleModule
{
    long Errors;
protected:
    virtual void initialize() override;
    void handleMessage(cMessage *msg) override;
};

Define_Module(HSR_Error_Inducer);


void HSR_Error_Inducer::initialize()
{
    Errors=0;
    char buf[40];
     sprintf(buf, "Errors Induced: %ld", Errors);
    this->getDisplayString().setTagArg("t",0,buf);
}

void HSR_Error_Inducer::handleMessage(cMessage *msg) {

    //error generation
        int geterr=this->par("MsgErrorRate");
        int E;
        if (geterr!=0)
        {
            E=rand()%geterr;
        }else
        {
            E=0;
        }

        if (E==1)
        {
            Errors++;
            delete msg;
        }else
        {
            if (strcmp(msg->getArrivalGate()->getName(), "A$i")==0)
                    {
                        send(msg,"B$o");
                    }else
                    {
                        send(msg,"A$o");
                    }
        }
        char buf[40];
         sprintf(buf, "Errors Induced: %ld", Errors);
        this->getDisplayString().setTagArg("t",0,buf);

}


