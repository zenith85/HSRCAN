/*
 * CANphy.cc
 *
 *  Created on: Nov 7, 2020
 *      Author: ibrah
 */

#include <omnetpp.h>
#include <stdio.h>

using namespace omnetpp;

//declare public variables
bool sof=0;                      //sof is the start of the frame 0 is true 1 is false           type of bool 1 bit
//arbitter 11 bits               //arbit taken from the nod ID in the NED
unsigned char control=0;         //Control is an 7 bits modifier                                type of char 8 bits
long long data=0;                //Data is 1 to 8 bytes or 8x8=64 bits maximum                  type of long long 64 bits
unsigned short crc=1;            //CRC field 15 bits                                            type of shorts 16  bits
bool ack_slot_bit=0;             //ack slot bit 1 bit                                           type of bool 1 bit
bool delimitter=0;               //delimitter 1 bit                                             type of bool 1 bit
unsigned char eeof=127;            //End of frame 7 bits                                          type of char 8 bits

int bits=0;

//call and use all the omnetpp libraries
//bool sender_permission;
class CANphy: public cModule {

protected:
    void initialize() override;
};
class Arbiter: public cSimpleModule {
protected:
    void initialize() override; //called at the begining of simulation
};
class Control: public cSimpleModule {

    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
};
class Data: public cSimpleModule {

    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
};
class CRC: public cSimpleModule {

    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
};
class Ender: public cSimpleModule {

    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
};
class SINK: public cSimpleModule {
protected:
    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
};
class CANLogic: public cSimpleModule //cSimplemodule is the base class and Node is the inherited class
{
protected:
    void initialize() override; //called at the begining of simulation
    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
    void activity(cMessage *msg);
};

Define_Module(CANLogic);
Define_Module(Arbiter);
Define_Module(Control);
Define_Module(Data);
Define_Module(CRC);
Define_Module(Ender);
Define_Module(SINK);

void msgreport()
{
    bits++;
    EV<<"this is bits ";
    EV<<bits;
}

void CANLogic::initialize() {

    if (strcmp("Sender", getParentModule()->getName()) == 0) {

    }
}

void Arbiter::initialize() {
    //arbiter is the one that decide to send based on the ID (sender (send),else (listen))
    //sender parameter is defined in the NED file

    bool nodetype = getParentModule()->par("Sender").boolValue();
    if (nodetype == true) {
        cMessage *msg = new cMessage("");
        msg->addPar("msgSOF_1b");
        msg->par("msgSOF_1b").setLongValue(sof);
        msg->addPar("msgID_11b");
        msg->par("msgID_11b").setLongValue(this->getParentModule()->par("ID").intValue());
        send(msg, "Arbiter_out");
    }
}

void Control::handleMessage(cMessage *msg) {
    msg->addPar("msgControl_7b");
    msg->par("msgControl_7b").setLongValue(1);
    send(msg, "Control_out");
}
void Data::handleMessage(cMessage *msg) {
    msg->addPar("msgData_8B");
    msg->par("msgData_8B").setLongValue(data);
    send(msg, "Data_out");
}
void CRC::handleMessage(cMessage *msg) {
    msg->addPar("msgCRC_15b");
    msg->par("msgCRC_15b").setLongValue(crc);
    send(msg, "CRC_out");
}
void Ender::handleMessage(cMessage *msg) {
    msg->addPar("msgACK_1b");
    msg->par("msgACK_1b").setLongValue(ack_slot_bit);
    msg->addPar("msgDEL_1b");
    msg->par("msgDEL_1b").setLongValue(delimitter);
    msg->addPar("msgEOF_7b");
    msg->par("msgEOF_7b").setLongValue(eeof);
    send(msg, "Ender_out");
}
void SINK::handleMessage(cMessage *msg) {
    this->bubble(msg->getName());
    this->bubble("arrived");
}

cMessage *SPI_OUT(cMessage *msg, const char *par, int offset)
{
    cMessage *dom_res = new cMessage("");

    if ((msg->par(par).longValue()>>offset)&1)
    {
        dom_res->setName("resessive");
        return dom_res;

    }else
    {
        dom_res->setName("dominant");
        return dom_res;
    }

    return dom_res;
}

void CANLogic::handleMessage(cMessage *msg) {
    if (strcmp(msg->getArrivalGate()->getName(),"CANlogic_outbound_in"))
    {
        EV<<"this is messge ";
        EV<<msg->par("msgSOF_1b").longValue();
        //1. send the sof
        for (int i=0;i<1;i++)
        {
            send(SPI_OUT(msg, "msgSOF_1b", i),"CANlogic_outbound_out");
            msgreport();
        }
        //2. send the arbitration
        for (int i=0;i<11;i++)
        {
            send(SPI_OUT(msg, "msgID_11b", i),"CANlogic_outbound_out");
            msgreport();
        }

        //3. send the control
        for (int i=0;i<7;i++)
        {
            send(SPI_OUT(msg, "msgControl_7b",i),"CANlogic_outbound_out");
            msgreport();
        }
        //4. send the data
        for (int i=0;i<64;i++)
        {
            send(SPI_OUT(msg, "msgData_8B",i),"CANlogic_outbound_out");
            msgreport();
        }
        //5. send the CRC

        for (int i=0;i<15;i++)
        {
            send(SPI_OUT(msg, "msgCRC_15b",i),"CANlogic_outbound_out");
            msgreport();
        }

        //6. send the ack
        for (int i=0;i<1;i++)
        {
            send(SPI_OUT(msg, "msgACK_1b",i),"CANlogic_outbound_out");
            msgreport();
        }

        //7. send the delimitter
        for (int i=0;i<1;i++)
        {
            send(SPI_OUT(msg, "msgDEL_1b",i),"CANlogic_outbound_out");
            msgreport();
        }

        //8. send the EOF
        SPI_OUT(msg, "msgEOF_7b", 7);
        for (int i=0;i<7;i++)
        {
            send(SPI_OUT(msg, "msgEOF_7b",i),"CANlogic_outbound_out");
            msgreport();
        }
    }
}


