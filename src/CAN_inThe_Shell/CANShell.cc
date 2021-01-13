/*
 * CANphy.cc
 *
 *  Created on: Nov 7, 2020
 *      Author: ibrah
 */

#include <omnetpp.h>
#include <stdio.h>
#include <iostream>

using namespace omnetpp;

//declare public variables
bool sof=0;                      //sof is the start of the frame 0 is true 1 is false           type of bool 1 bit
//arbitter 11 bits               //arbit taken from the nod ID in the NED
unsigned char control=0;         //Control is an 7 bits modifier                                type of char 8 bits
long long data=0;                //Data is 1 to 8 bytes or 8x8=64 bits maximum                  type of long long 64 bits
unsigned short crc=1;            //CRC field 15 bits                                            type of shorts 16  bits
bool ack_slot_bit=0;             //ack slot bit 1 bit                                           type of bool 1 bit
bool delimitter=0;               //delimitter 1 bit                                             type of bool 1 bit
unsigned char eeof=127;          //End of frame 7 bits                                          type of char 8 bits

//call and use all the omnetpp libraries
bool ErrorFLag;
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
    int framesent=0;
    int framesrcvd=0;
    int errorsdetected=0;
protected:
    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
    void finish() override;
};
class CANLogic: public cSimpleModule //cSimplemodule is the base class and Node is the inherited class
{
    int bufferwalker=0;
    int framesent=0;
    int framesrcvd=0;
    int errorsdetected=0;
private:
    cMessage *event;
    cMessage *comMsg;
public:
    CANLogic();
    virtual~CANLogic();
protected:
    void initialize() override; //called at the begining of simulation
    void handleMessage(cMessage *msg) override; //handle whenever message arrive at the node
    void finish() override;
};

Define_Module(CANLogic);
CANLogic::CANLogic()
{
    event=comMsg=NULL;
    comMsg=NULL;
}
CANLogic::~CANLogic()
{
    cancelAndDelete(event);
    delete comMsg;
}
Define_Module(Arbiter);
Define_Module(Control);
Define_Module(Data);
Define_Module(CRC);
Define_Module(Ender);
Define_Module(SINK);

void msgreport()
{
}

void Arbiter::initialize() {
    //arbiter is the one that decide to send based on the ID (sender (send),else (listen))
    //sender parameter is defined in the NED file

    bool nodetype = getParentModule()->par("Sender").boolValue();
    if (nodetype == true) {
        cMessage *msg = new cMessage("inside_msg");
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
    //how many messages are received
    if (strcmp(msg->getName(),"Success")==0)
    {
        //messages_received+=1;
        this->getParentModule()->par("messages_received").setIntValue(this->getParentModule()->par("messages_received").intValue()+1);
    }else
    {
        //errors_received+=1;
        ErrorFLag=true;
        this->getParentModule()->par("errors_received").setIntValue(this->getParentModule()->par("errors_received").intValue()+1);
    }

    //messages_received+=1;
    //display update
    framesrcvd=this->getParentModule()->par("messages_received").intValue();
    framesent=this->getParentModule()->par("frame_sent").intValue();
    errorsdetected=this->getParentModule()->par("errors_received").intValue();
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld error: %ld", framesrcvd, framesent,errorsdetected);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);

}
void SINK::finish()
{
    EV<<"Messages received by ";
    EV<<this->getParentModule()->getName();
    EV<<"(";
    //EV<<this->par("msgrcvd").intValue();
    //EV<< messages_received;
    EV<<")";
    //cancelAndDelete(event);
    //delete comMsg;
}
//Serial Peripheral Interface for sending out
cMessage *SPI_OUT(cMessage *msg, const char *par, int offset)
{
    cMessage *dom_res = new cMessage("");

    //frame_sent+=1;


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


void CANLogic::initialize() {
    event=new cMessage("event");
    //    bool nodetype = getParentModule()->par("Sender").boolValue();
    //    if (nodetype == true) {
    //        comMsg=new cMessage("comMsg");
    //        scheduleAt(5, event);
    //    }

    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld error: %ld", framesrcvd, framesent,errorsdetected);
    getParentModule()->getDisplayString().setTagArg("t",0,buf);
}


//void CANLogic::handleMessage(cMessage *msg)
//{
//    if (msg==event){
//        send(comMsg,"CANLogicInterface$o");
//        comMsg=NULL;
//    }
//    else
//    {
//        cancelEvent(event);
//        comMsg=msg;
//        scheduleAt(simTime()+1, event);
//    }
//
//}

void CANLogic::handleMessage(cMessage *msg)
{

    if (strcmp(msg->getName(),"inside_msg")==0)
    {
        comMsg=msg;
        if (event!=NULL)
        {
            cancelEvent(event);
        }
        scheduleAt(simTime()+1, event);
    }
    if (msg==event) //here is the selfmsg that tell us to send after (t-1)
    {
        //this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
        cancelEvent(event);
        //for (int i=0;i<1;i++)//1. send the sof
        if (bufferwalker==0)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgSOF_1b", bufferwalker),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<11;i++)//2. send the arbitration
        if (bufferwalker>0 and bufferwalker <11)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgID_11b", (bufferwalker-1)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //if (bufferwalker==11//for (int i=0;i<7;i++)//3. send the control
        if (bufferwalker>10 and bufferwalker <18)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgControl_7b",(bufferwalker-11)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<64;i++)//4. send the data
        if (bufferwalker>17 and bufferwalker<82)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgData_8B",(bufferwalker-18)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<15;i++)//5. send the CRC
        if (bufferwalker>81 and bufferwalker <97)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgCRC_15b",(bufferwalker-82)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<1;i++)//6. send the ack
        if (bufferwalker>96 and bufferwalker <98)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgACK_1b",(bufferwalker-97)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<1;i++)
        if (bufferwalker>97  and bufferwalker <99)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgDEL_1b",(bufferwalker-98)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //for (int i=0;i<7;i++)//8. send the EOF
        if (bufferwalker>98  and bufferwalker <107)
        {
            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
            sendDelayed(SPI_OUT(comMsg, "msgEOF_7b",(bufferwalker-99)),0.05,"CANLogicInterface$o");
            bufferwalker++;
        }
        //reschedule for the next sending
        if (bufferwalker<107)
        {

            scheduleAt(simTime()+1, event);
        }else
        {
            //cancelAndDelete(event);
            bufferwalker=0;
        }
        //display update
        framesent=this->getParentModule()->par("frame_sent").intValue();
        framesrcvd=this->getParentModule()->par("messages_received").intValue();
        errorsdetected=this->getParentModule()->par("errors_received").intValue();
        char buf[40];
        sprintf(buf, "rcvd: %ld sent: %ld error: %ld", framesrcvd, framesent,errorsdetected);
        getParentModule()->getDisplayString().setTagArg("t",0,buf);
    }
        //if (strcmp(msg->getArrivalGate()->getName(),"CANLogicInterface$i")==0)
        if (((strcmp(msg->getName(),"resessive")==0) or (strcmp(msg->getName(),"dominant")==0) or  (strcmp(msg->getName(),"Error")==0)))
        {
            cMessage *bitwise = new cMessage("");
            const char *name=msg->getName();
            //we should forward them to the sink
            if ((strcmp(name,"resessive")==0) or (strcmp(name,"dominant")==0))
            {
                bitwise->setName("Success");
            }
            else
            {
                bitwise->setName("Error");
                bufferwalker=0;

            }
            send(bitwise, "CANlogic_inbound_out");
        }
}
void CANLogic::finish()
{
}

//void CANLogic::handleMessage(cMessage *msg) {
//    //if we received a message from inside to go out
//    if (strcmp(msg->getArrivalGate()->getName(),"CANlogic_inbound_in")==0 && !ErrorFLag)
//    {
//        //EV<<"this is messge ";
//        //EV<<msg->par("msgSOF_1b").longValue();
//        //1. send the sof
//        for (int i=0;i<1;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgSOF_1b", i),0.05,"CANLogicInterface$o");
//            // msgreport();
//
//        }
//        //2. send the arbitration
//        for (int i=0;i<11;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgID_11b", i),0.05,"CANLogicInterface$o");
//            //msgreport();
//        }
//
//        //3. send the control
//        for (int i=0;i<7;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgControl_7b",i),0.05,"CANLogicInterface$o");
//            // msgreport();
//        }
//        //4. send the data
//        for (int i=0;i<64;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgData_8B",i),0.05,"CANLogicInterface$o");
//            //msgreport();
//        }
//        //5. send the CRC
//
//        for (int i=0;i<15;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgCRC_15b",i),0.05,"CANLogicInterface$o");
//            //msgreport();
//        }
//
//        //6. send the ack
//        for (int i=0;i<1;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgACK_1b",i),0.05,"CANLogicInterface$o");
//            // msgreport();
//        }
//
//        //7. send the delimitter
//        for (int i=0;i<1;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgDEL_1b",i),0.05,"CANLogicInterface$o");
//            //msgreport();
//        }
//
//        //8. send the EOF
//        SPI_OUT(msg, "msgEOF_7b", 7);
//        for (int i=0;i<7;i++)
//        {
//            this->getParentModule()->par("frame_sent").setIntValue(this->getParentModule()->par("frame_sent").intValue()+1);
//            sendDelayed(SPI_OUT(msg, "msgEOF_7b",i),0.05,"CANLogicInterface$o");
//            //msgreport();
//        }
//        //display update
//        framesrcvd=this->getParentModule()->par("messages_received").intValue();
//        framesent=this->getParentModule()->par("frame_sent").intValue();
//        errorsdetected=this->getParentModule()->par("errors_received").intValue();
//        char buf[40];
//        sprintf(buf, "rcvd: %ld sent: %ld error: %ld", framesrcvd, framesent,errorsdetected);
//        getParentModule()->getDisplayString().setTagArg("t",0,buf);
//    }
//    //if we received a message from outside to go in
//    if (strcmp(msg->getArrivalGate()->getName(),"CANLogicInterface$i")==0)
//    {
//        cMessage *bitwise = new cMessage("");
//        const char *name=msg->getName();
//        //we should forward them to the sink
//        if ((strcmp(name,"resessive")==0) or (strcmp(name,"dominant")==0))
//        {
//            bitwise->setName("Success");
//        }
//        else
//        {
//            bitwise->setName("Error");
//
//        }
//        send(bitwise, "CANlogic_inbound_out");
//    }
//}


