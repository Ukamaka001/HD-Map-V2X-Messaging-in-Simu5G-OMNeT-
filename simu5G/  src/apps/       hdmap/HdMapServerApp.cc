#include "apps/hdmap/HdMapServerApp.h"
#include "apps/hdmap/HdMapPacket_m.h"

#include <inet/common/packet/Packet.h>
#include <inet/transportlayer/common/L4PortTag_m.h>
#include <inet/networklayer/common/L3AddressTag_m.h>

Define_Module(inet::HdMapServerApp);

using namespace inet;
using namespace omnetpp;

HdMapServerApp::~HdMapServerApp()
{
    if (initTrafficMsg_) cancelAndDelete(initTrafficMsg_);
}

void HdMapServerApp::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage != INITSTAGE_APPLICATION_LAYER)
        return;

    initTrafficMsg_ = new cMessage("initTraffic");

    localPort_ = par("localPort");
    tos_       = par("tos");

    scheduleAt(simTime(), initTrafficMsg_);
}

void HdMapServerApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (msg == initTrafficMsg_)
            initTraffic();
        return;
    }

    auto pk = check_and_cast<Packet *>(msg);
    auto req = check_and_cast<HdMapPacket *>(pk->decapsulate());

    auto respPk = new Packet("HdMapResp");
    auto resp = new HdMapPacket("HdMapPacket");
    resp->setSeq(req->getSeq());
    resp->setVehicleId(req->getVehicleId());
    resp->setIsResponse(true);
    resp->setTileId(req->getTileId());
    resp->setPayloadSize(req->getPayloadSize());
    resp->setByteLength(req->getByteLength());

    auto srcAddr = pk->getTag<L3AddressInd>()->getSrcAddress();
    auto srcPort = pk->getTag<L4PortInd>()->getSrcPort();

    respPk->encapsulate(resp);
    socket.sendTo(respPk, srcAddr, srcPort);

    delete req;
    delete pk;
}

void HdMapServerApp::initTraffic()
{
    socket.setOutputGate(gate("socketOut"));

    if (localPort_ < 0)
        socket.bind(0);
    else
        socket.bind(localPort_);

    if (tos_ != -1)
        socket.setTos(tos_);
}
