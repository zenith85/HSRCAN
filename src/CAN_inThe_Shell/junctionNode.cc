//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "junctionNode.h"
#include <stdio.h>
#include <iostream>
Define_Module(JunctionNode);
double delayvalue=0.03;

void JunctionNode::initialize()
{
    // if the delay value is not identified, then it will be 0.03 otherwise it will take the value of the delay itself
    if (this->par("Delay").doubleValue()!=0)
    {
        delayvalue=this->par("Delay").doubleValue();

    }
    else
    {
        this->par("Delay").setDoubleValue(delayvalue);
    }
}

void JunctionNode::handleMessage(cMessage *msg)
{
    int gt=this->gateCount()/2;
    for (int i=0;i < gt ;i++)
    {
       // EV<<gate("JunctionInterface$i", i)->getIndex();
        if (gate("JunctionInterface$o", i)->getIndex() != msg->getArrivalGate()->getIndex())
        {
               //send(msg->dup(), "JunctionInterface$o",i);
            //send delayed can simulate the wire length delay
            //section 4.7.4 delayed sending omnet manual
            // here 0.003 delay is suggested, please consolt a reference before changing this number
            sendDelayed(msg->dup(),delayvalue, "JunctionInterface$o",i);
        }
    }
}

