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
// TODO documentation
//
network CAN_SIM_SIMPLE
{
    @display("bgb=680,459");
    submodules:
        caNshell: CANshell {
            @display("p=553,197");
            Sender = true;
            ID = 1;
        }
        caNshell1: CANshell {
            @display("p=170,200");
            Sender = false;
            ID = 2;
        }
        canBus: CANBus {
            @display("p=356,199");
        }
    connections:
        caNshell.phy_interface <--> canBus.CANBus_inout++;
        caNshell1.phy_interface <--> canBus.CANBus_inout++;
}

