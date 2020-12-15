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
import hsrcan.CAN_inThe_Shell.JunctionNode;




//
// TODO auto-generated type
//
network CAN_SIM
{
    @display("bgb=1031.9563,468.96,#408080;bgi=background/car");

    types:
        simple CAN_Node
        {
            gates:
                input input_gate;
                output output_gate;
        }

    submodules:
        caNshell: CANshell {
            @display("p=908.2125,177.24376");
            Sender = true;
            ID = 0;
        }
        canBus: CANBus {
            @display("p=292.3875,214.76251");
        }
        caNshell1: CANshell {
            @display("p=155.25,302.73752");
            Sender = false;
            ID = 1;
        }
        Socket4: JunctionNode {
            @display("p=908.2125,288.50626");
            Delay = 0.003;
        }
        caNshell3: CANshell {
            @display("p=908.2125,386.83127");
            Sender = false;
            ID = 3;
        }
        Socket1: JunctionNode {
            @display("p=371.30627,288.50626");
            Delay = 0.03;
        }
        caNshell2: CANshell {
            @display("p=371.30627,139.725");
            Sender = false;
            ID = 2;
        }
        caNshell4: CANshell {
            @display("p=291.09375,363.54376");
            Sender = false;
            ID = 5;
        }
        Socket3: JunctionNode {
            @display("p=155.25,217.35");
        }
        Socket5: JunctionNode {
            @display("p=291.09375,139.725");
        }
        Socket2: JunctionNode {
            @display("p=371.30627,349.3125");
        }
        caNshell5: CANshell {
            @display("p=464.45627,349.3125");
            Sender = false;
            ID = 5;
        }
    connections:
        caNshell.phy_interface <--> Socket4.JunctionInterface++;
        Socket4.JunctionInterface++ <--> caNshell3.phy_interface;
        Socket4.JunctionInterface++ <--> Socket1.JunctionInterface++;
        Socket1.JunctionInterface++ <--> canBus.CANBus_inout++;
        canBus.CANBus_inout++ <--> Socket5.JunctionInterface++;
        Socket5.JunctionInterface++ <--> caNshell2.phy_interface;
        canBus.CANBus_inout++ <--> Socket3.JunctionInterface++;
        Socket3.JunctionInterface++ <--> caNshell1.phy_interface;
        caNshell4.phy_interface <--> canBus.CANBus_inout++;
        caNshell5.phy_interface <--> Socket2.JunctionInterface++;
        Socket2.JunctionInterface++ <--> Socket1.JunctionInterface++;
}
