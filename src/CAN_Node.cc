/*
 * CAN_Node.cc
 *
 *  Created on: Nov 7, 2020
 *      Author: ibrah
 */




#include <omnetpp.h>

using namespace omnetpp; //call and use all the omnetpp libraries

class CAN_Node: public cSimpleModule //cSimplemodule is the base class and Node is the inherited class
{
protected:
    void initialize() override;//called at the begining of simulation
    void handleMessage(cMessage *msg) override;//handle whenever message arrive at the node

    };

Define_Module(CAN_Node);

void CAN_Node::initialize()
{
    if (strcmp("N1", getName())==0)
    {
        cMessage *msg=new cMessage("hey you");
        send(msg,"output_gate");
    }
    }

void CAN_Node::handleMessage(cMessage *msg)
{
    send(msg,"output_gate");///send message if you received the msg
    }

