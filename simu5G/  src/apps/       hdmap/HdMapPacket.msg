namespace inet;

packet HdMapPacket
{
    int seq = 0;
    int vehicleId = -1;
    bool isResponse = false;
    string tileId = "";
    int payloadSize = 0;
}
