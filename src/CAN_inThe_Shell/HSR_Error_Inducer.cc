/*
 * CANBus.cc
 *
 *  Created on: Dec 8, 2020
 *      Author: ibrah
 */




#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <time.h>

using namespace omnetpp;


//class HSR_Error_Inducer: public cSimpleModule { //cSimplemodule is the base class and Node is the inherited class
//
//
//protected:
//    void initialize() override;
//};


class HSR_Error_Inducer: public cSimpleModule
{
    int BER=0;
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


//            struct timeval tv;
//            gettimeofday(&tv,NULL);
//           // unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;//find the microseconds for seeding srand()
//            unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;//find the microseconds for seeding srand()
//            srand(time_in_micros);

        int geterr=this->par("MsgErrorRate");
        int equivlinks=this->par("EquivLinks");
        //EV<<"geterr is ";
        //EV<<geterr;
        int E;
        if (geterr==0)
        {
            E=0;//case of no errors
        }
//        else if (geterr==1)
//        {
//            E=1;//case of all errors
//        }
        else
        {
            E=rand()%(geterr);
            EV<<this->getName();
            EV<<" rnd value =";
            EV<<E;

        }
        //if ((E==(geterr)/2)&&geterr!=0) //best case scenario seed pick

        //fixed destribution
//        if (BER>(geterr*geterr)){BER=0;}
//        BER=BER+1;
//        EV<<BER;
//        if ((BER==((geterr*geterr)/2)))

        if (((E==geterr/2)&&geterr!=0)||E==1) //worst case scenario seed pick
        {
            EV<<"Error induced";
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



