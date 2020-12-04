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

package hsrcan;

import hsrcan.CAN_inThe_Shell.CANshell;


//
// TODO auto-generated type
//
network Node
{
    @display("bgb=790,549");
    types:
        simple CAN_Node
        {
            gates:
                input input_gate;
                output output_gate;
        }

    submodules:
        N2: CAN_Node {
            @display("p=115.024,276.5");
        }
        caNshell: CANshell {
            @display("p=496.594,190.232");
            Sender = true;
            ID = 1;
        }
    connections:
        caNshell.CAN_phy_out --> {delay=100ms;} --> N2.input_gate;
        N2.output_gate --> {delay=100ms;} --> caNshell.CAN_phy_in;
}
