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

module CANshell
{
    @display("bgb=950,300,white;i=block/ifcard;bgi=background/CANfullframe");
    bool Sender; // this parameter should be changed in the NED to deicde if send or not
    int ID;// this is the ID number of the node
    gates:
        //these are the gates of the parents the shell
        //input CAN_phy_in;
        //output CAN_phy_out;
        inout phy_interface;

    types:
        simple CANLogic
        {
            @display("i=abstract/dispatcher");
            gates:
                //input CANlogic_outbound_in;
                //output CANlogic_outbound_out;
                inout CANLogicInterface;

                input CANlogic_inbound_in;

                output CANlogic_inbound_out;
        }

        simple Arbiter
        {
            @display("i=block/user");
            gates:
                //input Arbiter_in;
                output Arbiter_out;
        }

        simple Control
        {
            @display("i=block/control");
            gates:
                input Control_in;
                output Control_out;
        }

        simple Data
        {
            @display("i=block/buffer");
            gates:
                input Data_in;
                output Data_out;
        }

        simple CRC
        {
            @display("i=block/filter");
            gates:
                input CRC_in;
                output CRC_out;
        }

        simple Ender
        {
            @display("i=block/plug");
            gates:
                input Ender_in;
                output Ender_out;
        }

        simple SINK
        {
            @display("i=block/bucket");
            gates:
                input SINK_in;
        }

    submodules:
        canLogic: CANLogic {
            @display("p=867,230");
        }
        arbiter: Arbiter {
            @display("p=146,171");
        }
        data: Data {
            @display("p=453,171");
        }
        control: Control {
            @display("p=315,171");
        }
        crc: CRC {
            @display("p=688,171");
        }
        ender: Ender {
            @display("p=867,171");
        }
        sink: SINK {
            @display("p=718,230");
        }
    connections:
        arbiter.Arbiter_out --> control.Control_in;
        control.Control_out --> data.Data_in;
        data.Data_out --> crc.CRC_in;
        crc.CRC_out --> ender.Ender_in;
        ender.Ender_out --> canLogic.CANlogic_inbound_in;
        //canLogic.CANlogic_outbound_out --> CAN_phy_out;
        //CAN_phy_in --> canLogic.CANlogic_outbound_in;
        canLogic.CANlogic_inbound_out --> sink.SINK_in;
        canLogic.CANLogicInterface <--> phy_interface;
}
