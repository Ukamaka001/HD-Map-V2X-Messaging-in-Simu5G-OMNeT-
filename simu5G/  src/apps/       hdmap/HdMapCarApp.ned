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

package simu5g.apps.hdmap;

import inet.applications.contract.IApp;

simple HdMapCarApp like IApp
{
    parameters:
        @class(inet::HdMapCarApp);

        int localPort = default(-1);
        int destPort = default(4000);
        string destAddress;

        int packetSize = default(200);
        double sendInterval @unit(s) = default(1s);
        double startTime @unit(s) = default(0s);

        int tos = default(-1);
        int vehicleId = default(-1);
        string tileId = default("tile-A1");

        @signal[hdmapDelay](type=double);
        @statistic[hdmapDelay](title="HD Map RTT"; record=vector; unit="s");

        @display("i=block/source");
    gates:
        output socketOut;
        input socketIn;
}
