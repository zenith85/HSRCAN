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

package hsrcan.CAN_inThe_Shell;
//
// TODO documentation
//
module CANBus
{
    @display("i=block/transport;bgb=319,269");
    //@display("t=CAN BUS");

    //@display("t=Packets sent: 18;tt=Additional tooltip information");
	//@display("t=0");
    bool EOT;
    int BER;
    double Delay;
    gates:

        inout CANBus_inout[];

    types:
        simple SimpCANBus
        {
            @display("i=block/layer");
            gates:
                inout SCANB_interface[];
        }

    submodules:

        simpcanbus: SimpCANBus {
            @display("p=153,109");
        }
    connections:
        for i=0..sizeof(CANBus_inout)-1 {
            simpcanbus.SCANB_interface++ <--> {  delay = 5ms; } <--> CANBus_inout[i];
        }


}

