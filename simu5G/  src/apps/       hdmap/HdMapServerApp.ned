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

simple HdMapServerApp like IApp
{
    parameters:
        @class(inet::HdMapServerApp);

        int localPort = default(4000);
        int tos = default(-1);

        @display("i=block/server");
    gates:
        input socketIn;
        output socketOut;
}
