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




//
// TODO auto-generated type
//
network CAN_SIM
{
    @display("bgb=790,549,#408080");
    types:
        simple CAN_Node
        {
            gates:
                input input_gate;
                output output_gate;
        }

    submodules:
        caNshell: CANshell {
            @display("p=496.594,190.232");
            Sender = true;
            ID = 1;
        }
        canBus: CANBus {
            @display("p=376.04,346.178");
            CON_NUM = 2;
        }
        caNshell1: CANshell {
            @display("p=222.306,190.232");
            Sender = false;
            ID = 2;
        }
    connections:
        canBus.CANBus_inout++ <--> caNshell.phy_interface;
        canBus.CANBus_inout++ <--> caNshell1.phy_interface;
}
