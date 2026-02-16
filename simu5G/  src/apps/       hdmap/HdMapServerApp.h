/*
 * HdMapServerApp.h
 *
 *  Created on: Jan 21, 2026
 *      Author: simu5g
 */


#ifndef APPS_HDMAP_HDMAPSERVERAPP_H_
#define APPS_HDMAP_HDMAPSERVERAPP_H_

#include <omnetpp.h>

#include <inet/common/INETDefs.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/networklayer/common/L3Address.h>

namespace inet {

class HdMapServerApp : public omnetpp::cSimpleModule
{
  public:
    HdMapServerApp() = default;
    virtual ~HdMapServerApp();

  protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

  protected:
    void initTraffic();

  protected:
    omnetpp::cMessage *initTrafficMsg_ = nullptr;

    UdpSocket socket;

    int localPort_ = -1;
    int tos_ = -1;
};

} // namespace inet

#endif
