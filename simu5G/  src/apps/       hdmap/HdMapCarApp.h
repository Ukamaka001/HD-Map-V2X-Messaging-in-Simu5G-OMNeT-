#ifndef APPS_HDMAP_HDMAPCARAPP_H_
#define APPS_HDMAP_HDMAPCARAPP_H_

#include <omnetpp.h>
#include <string>
#include <unordered_map>

#include <inet/common/INETDefs.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

namespace inet {

class HdMapCarApp : public omnetpp::cSimpleModule
{
  public:
    HdMapCarApp() = default;
    virtual ~HdMapCarApp() override;

  protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

  protected:
    void initTraffic();
    void sendHdMapRequest();

  protected:
    // timers
    omnetpp::cMessage *selfSender_ = nullptr;
    omnetpp::cMessage *initTrafficMsg_ = nullptr;

    // socket + addressing
    UdpSocket socket;
    L3Address destAddress_;

    // params
    int localPort_ = -1;
    int destPort_  = 4000;
    int packetSize_ = 200;
    omnetpp::simtime_t sendInterval_ = 1;
    omnetpp::simtime_t startTime_ = 0;
    int tos_ = -1;

    int vehicleId_ = -1;
    std::string tileId_ = "tile-A1";
    int seq_ = 0;

    // delay measurement
    omnetpp::simsignal_t hdmapDelaySignal = -1;
    std::unordered_map<int, omnetpp::simtime_t> sentTimeBySeq;
};

} // namespace inet

#endif
