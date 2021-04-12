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
    @display("bgb=1383.8462,1000.00006");
    submodules:
        caNshell: CANshell {
            @display("p=550,530.7692");
            NumFrames = 50000;
            Sender = true;
            ID = 1;
        }
        caNtoHSR: CANtoHSR {
            @display("p=550,416.9231");
            NodeID = "alpha";
            msgError = 0;
            Delay = 0;
        }
        caNtoHSR2: CANtoHSR {
            @display("p=550,191.53847");
            NodeID = "beta";
            msgError = 0;
            Delay = 0;
        }
        caNshell2: CANshell {
            @display("p=552.30774,90");
            NumFrames = 50000;
            Sender = false;
            ID = 3;
        }
        hsr_Error_Inducer11: HSR_Error_Inducer {
            @display("p=763.04,303.20798");
            EquivLinks = 1;

        }
        hsr_Error_Inducer13: HSR_Error_Inducer {
            @display("p=355.416,349.392");
            EquivLinks = 1;

        }
    connections:
        caNshell.phy_interface <--> caNtoHSR.CANtoHSR_inout;
        caNtoHSR2.CANtoHSR_inout <--> caNshell2.phy_interface;
        hsr_Error_Inducer11.B <--> caNtoHSR2.HSR_2;
        hsr_Error_Inducer13.B <--> caNtoHSR2.HSR_1;
        caNtoHSR.HSR_1 <--> hsr_Error_Inducer11.A;
        caNtoHSR.HSR_2 <--> hsr_Error_Inducer13.A;
}

