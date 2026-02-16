#include "apps/hdmap/HdMapCarApp.h"
#include "apps/hdmap/HdMapPacket_m.h"

#include <inet/common/packet/Packet.h>

Define_Module(inet::HdMapCarApp);

using namespace inet;
using namespace omnetpp;

HdMapCarApp::~HdMapCarApp()
{
    cancelAndDelete(selfSender_);
    cancelAndDelete(initTrafficMsg_);
}

void HdMapCarApp::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage != INITSTAGE_APPLICATION_LAYER)
        return;

    hdmapDelaySignal = registerSignal("hdmapDelay");

    selfSender_     = new cMessage("selfSender");
    initTrafficMsg_ = new cMessage("initTraffic");

    localPort_    = par("localPort");
    destPort_     = par("destPort");
    packetSize_   = par("packetSize");
    sendInterval_ = par("sendInterval");
    startTime_    = par("startTime");
    tos_          = par("tos");
    vehicleId_    = par("vehicleId");
    tileId_       = par("tileId").stdstringValue();

    seq_ = 0;
    scheduleAt(simTime(), initTrafficMsg_);
}

void HdMapCarApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (msg == initTrafficMsg_) {
            initTraffic();
        }
        else if (msg == selfSender_) {
            sendHdMapRequest();
            scheduleAt(simTime() + sendInterval_, selfSender_);
        }
        return;
    }

    auto pk = check_and_cast<Packet *>(msg);

    cPacket *inner = pk->decapsulate();
    auto resp = check_and_cast<HdMapPacket *>(inner);

    int respSeq = resp->getSeq();

    auto it = sentTimeBySeq.find(respSeq);
    if (it != sentTimeBySeq.end()) {
        simtime_t rtt = simTime() - it->second;
        emit(hdmapDelaySignal, rtt.dbl());
        sentTimeBySeq.erase(it);
    }

    delete resp;
    delete pk;
}

void HdMapCarApp::initTraffic()
{
    socket.setOutputGate(gate("socketOut"));

    if (localPort_ < 0)
        socket.bind(0);
    else
        socket.bind(localPort_);

    if (tos_ != -1)
        socket.setTos(tos_);

    const char *dest = par("destAddress");
    destAddress_ = L3AddressResolver().resolve(dest);

    scheduleAt(simTime() + startTime_, selfSender_);
}

void HdMapCarApp::sendHdMapRequest()
{
    auto pk = new Packet("HdMapReq");

    auto req = new HdMapPacket("HdMapPacket");

    int mySeq = seq_++;
    req->setSeq(mySeq);
    req->setVehicleId(vehicleId_);
    req->setIsResponse(false);
    req->setTileId(tileId_.c_str());
    req->setPayloadSize(packetSize_);

    // makes OMNeT++ count your packet size properly
    req->setByteLength(packetSize_);

    sentTimeBySeq[mySeq] = simTime();

    pk->encapsulate(req);
    socket.sendTo(pk, destAddress_, destPort_);
}
