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
        hsr_Error_Inducer8: HSR_Error_Inducer {
            @display("p=1093.8462,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer1: HSR_Error_Inducer {
            @display("p=1050.7693,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer3: HSR_Error_Inducer {
            @display("p=953.8462,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer4: HSR_Error_Inducer {
            @display("p=902.30774,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer5: HSR_Error_Inducer {
            @display("p=846.9231,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer6: HSR_Error_Inducer {
            @display("p=786.1539,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer7: HSR_Error_Inducer {
            @display("p=1002.30774,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer9: HSR_Error_Inducer {
            @display("p=734.6154,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer10: HSR_Error_Inducer {
            @display("p=683.07697,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer11: HSR_Error_Inducer {
            @display("p=631.5385,247.69232");
            EquivLinks = 1;

        }
        hsr_Error_Inducer21: HSR_Error_Inducer {
            @display("p=683.07697,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer22: HSR_Error_Inducer {
            @display("p=1093.8462,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer23: HSR_Error_Inducer {
            @display("p=953.8462,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer24: HSR_Error_Inducer {
            @display("p=1002.30774,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer25: HSR_Error_Inducer {
            @display("p=785.38464,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer26: HSR_Error_Inducer {
            @display("p=902.30774,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer27: HSR_Error_Inducer {
            @display("p=1050.7693,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer28: HSR_Error_Inducer {
            @display("p=846.9231,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer29: HSR_Error_Inducer {
            @display("p=734.6154,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer30: HSR_Error_Inducer {
            @display("p=631.5385,312.3077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer12: HSR_Error_Inducer {
            @display("p=455.38464,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer13: HSR_Error_Inducer {
            @display("p=498.46155,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer14: HSR_Error_Inducer {
            @display("p=358.46155,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer15: HSR_Error_Inducer {
            @display("p=87.692314,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer20: HSR_Error_Inducer {
            @display("p=36.153847,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer52: HSR_Error_Inducer {
            @display("p=406.9231,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer58: HSR_Error_Inducer {
            @display("p=358.46155,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer60: HSR_Error_Inducer {
            @display("p=306.9231,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer63: HSR_Error_Inducer {
            @display("p=87.692314,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer64: HSR_Error_Inducer {
            @display("p=36.153847,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer67: HSR_Error_Inducer {
            @display("p=306.9231,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer68: HSR_Error_Inducer {
            @display("p=190,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer70: HSR_Error_Inducer {
            @display("p=251.53847,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer72: HSR_Error_Inducer {
            @display("p=139.23077,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer73: HSR_Error_Inducer {
            @display("p=406.9231,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer75: HSR_Error_Inducer {
            @display("p=498.46155,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer76: HSR_Error_Inducer {
            @display("p=190.76924,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer78: HSR_Error_Inducer {
            @display("p=251.53847,319.23077");
            EquivLinks = 1;

        }
        hsr_Error_Inducer79: HSR_Error_Inducer {
            @display("p=455.38464,254.61539");
            EquivLinks = 1;

        }
        hsr_Error_Inducer80: HSR_Error_Inducer {
            @display("p=139.23077,254.61539");
            EquivLinks = 1;

        }
    connections:
        caNshell.phy_interface <--> caNtoHSR.CANtoHSR_inout;
        caNtoHSR2.CANtoHSR_inout <--> caNshell2.phy_interface;
        hsr_Error_Inducer8.B <--> hsr_Error_Inducer1.A;
        hsr_Error_Inducer1.B <--> hsr_Error_Inducer7.A;
        hsr_Error_Inducer7.B <--> hsr_Error_Inducer3.A;
        hsr_Error_Inducer3.B <--> hsr_Error_Inducer4.A;
        hsr_Error_Inducer4.B <--> hsr_Error_Inducer5.A;
        hsr_Error_Inducer5.B <--> hsr_Error_Inducer6.A;
        hsr_Error_Inducer6.B <--> hsr_Error_Inducer9.A;
        hsr_Error_Inducer9.B <--> hsr_Error_Inducer10.A;
        hsr_Error_Inducer10.B <--> hsr_Error_Inducer11.A;
        hsr_Error_Inducer11.B <--> caNtoHSR2.HSR_2;
        hsr_Error_Inducer22.B <--> hsr_Error_Inducer27.A;
        hsr_Error_Inducer27.B <--> hsr_Error_Inducer24.A;
        hsr_Error_Inducer24.B <--> hsr_Error_Inducer23.A;
        hsr_Error_Inducer23.B <--> hsr_Error_Inducer26.A;
        hsr_Error_Inducer26.B <--> hsr_Error_Inducer28.A;
        hsr_Error_Inducer28.B <--> hsr_Error_Inducer25.A;
        hsr_Error_Inducer25.B <--> hsr_Error_Inducer29.A;
        hsr_Error_Inducer29.B <--> hsr_Error_Inducer21.A;
        hsr_Error_Inducer21.B <--> hsr_Error_Inducer30.A;
        hsr_Error_Inducer8.A <--> hsr_Error_Inducer22.A;
        hsr_Error_Inducer13.B <--> hsr_Error_Inducer79.A;
        hsr_Error_Inducer79.B <--> hsr_Error_Inducer73.A;
        hsr_Error_Inducer73.B <--> hsr_Error_Inducer14.A;
        hsr_Error_Inducer14.B <--> hsr_Error_Inducer67.A;
        hsr_Error_Inducer67.B <--> hsr_Error_Inducer70.A;
        hsr_Error_Inducer70.B <--> hsr_Error_Inducer76.A;
        hsr_Error_Inducer76.B <--> hsr_Error_Inducer80.A;
        hsr_Error_Inducer80.B <--> hsr_Error_Inducer63.A;
        hsr_Error_Inducer63.B <--> hsr_Error_Inducer20.A;
        hsr_Error_Inducer75.B <--> hsr_Error_Inducer12.A;
        hsr_Error_Inducer12.B <--> hsr_Error_Inducer52.A;
        hsr_Error_Inducer52.B <--> hsr_Error_Inducer58.A;
        hsr_Error_Inducer58.B <--> hsr_Error_Inducer60.A;
        hsr_Error_Inducer60.B <--> hsr_Error_Inducer78.A;
        hsr_Error_Inducer78.B <--> hsr_Error_Inducer68.A;
        hsr_Error_Inducer68.B <--> hsr_Error_Inducer72.A;
        hsr_Error_Inducer72.B <--> hsr_Error_Inducer15.A;
        hsr_Error_Inducer15.B <--> hsr_Error_Inducer64.A;
        hsr_Error_Inducer13.A <--> hsr_Error_Inducer75.A;
        hsr_Error_Inducer20.B <--> caNtoHSR2.HSR_1;
        caNtoHSR.HSR_1 <--> hsr_Error_Inducer30.B;
        caNtoHSR.HSR_2 <--> hsr_Error_Inducer64.B;
}

