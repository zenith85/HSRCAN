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

package hsrcan.simulations;
import hsrcan.CAN_inThe_Shell.CANBus;
import hsrcan.CAN_inThe_Shell.CANshell;
import hsrcan.CAN_inThe_Shell.CANtoHSR;
import hsrcan.CAN_inThe_Shell.HSR_Error_Inducer;
import ned.IUnidirectionalChannel;


//
// TODO documentation
//
network CANHSR_SIM_SIMPLE
{
    @display("bgb=1118,799");
    submodules:
        caNshell: CANshell {
            @display("p=574,390");
            Sender = true;
            ID = 1;
        }
        caNshell1: CANshell {
            @display("p=118,390");
            Sender = false;
            ID = 2;
        }
        caNtoHSR: CANtoHSR {
            @display("p=459,327");
            NodeID = "alpha";
            msgError = 0;
            Delay = 0;
        }
        caNtoHSR1: CANtoHSR {
            @display("p=225,327");
            NodeID = "gamma";
            msgError = 0;
            Delay = 0;
        }
        caNtoHSR2: CANtoHSR {
            @display("p=315,184");
            NodeID = "beta";
            msgError = 0;
            Delay = 0;
        }
        caNshell2: CANshell {
            @display("p=317,83");
            Sender = false;
            ID = 3;
        }
        hsr_Error_Inducer: HSR_Error_Inducer {
            @display("p=379,251");
            MsgErrorRate = 10;
        }
        hsr_Error_Inducer1: HSR_Error_Inducer {
            @display("p=274,251");
            MsgErrorRate = 80;
        }
        hsr_Error_Inducer2: HSR_Error_Inducer {
            @display("p=325,327");
            MsgErrorRate = 0;
        }
    connections:
        caNshell.phy_interface <--> caNtoHSR.CANtoHSR_inout;
        caNshell1.phy_interface <--> caNtoHSR1.CANtoHSR_inout;
        caNshell2.phy_interface <--> caNtoHSR2.CANtoHSR_inout;
        caNtoHSR.HSR_2 <--> hsr_Error_Inducer.A;
        hsr_Error_Inducer.B <--> caNtoHSR2.HSR_2;
        caNtoHSR1.HSR_1 <--> hsr_Error_Inducer1.A;
        hsr_Error_Inducer1.B <--> caNtoHSR2.HSR_1;
        caNtoHSR.HSR_1 <--> hsr_Error_Inducer2.A;
        hsr_Error_Inducer2.B <--> caNtoHSR1.HSR_2;
}

