
# HD Map V2X Messaging in Simu5G / OMNeT++ (TCP-Based)

A simulation project modeling bi-directional TCP communication between connected vehicles and an HD Map server using OMNeT++ 5.7.1, INET, and Simu5G.

This project evaluates how vehicles request HD map data over a reliable transport layer and receive structured responses under 5G NR network conditions.

---

## Overview

Modern autonomous and connected vehicles rely on High Definition (HD) Maps for:

- Lane-level localization  
- Curvature and geometry awareness  
- Road events (construction, speed updates, hazards)  
- Path planning refinement  

Unlike lightweight UDP beacons, HD map delivery requires:

- Reliability  
- Ordered delivery  
- Congestion control  
- Connection management  

This project implements that using TCP sessions between vehicle nodes and an HD Map server node inside a 5G simulation scenario.

---

## System Architecture

Vehicle (Client) ↔ 5G NR Network ↔ HD Map Server (TCP)

- HdMapCarApp  
  Initiates TCP connection and sends structured map requests.

- HdMapServerApp  
  Listens on TCP port, accepts connections, processes requests, and returns map data.

- HdMapPacket.msg  
  Defines the custom application-level message structure.

---

## Repository Structure

simu5G/
  src/
    apps/
      hdmap/
        HdMapPacket.msg
        HdMapCarApp.ned
        HdMapCarApp.cc
        HdMapCarApp.h
        HdMapServerApp.ned
        HdMapServerApp.cc
        HdMapServerApp.h

  simulations/
    NR/
      cars/
        Highway.ned
        HdMapSumoProject.ini
        heterogeneous.*.xml

---

## Requirements

- OMNeT++ 5.7.1  
- INET Framework (compatible version)  
- Simu5G  
- Linux or Windows OMNeT++ IDE environment  

---

## Build Instructions

1. Clone repository inside your OMNeT++ workspace  
2. Import project into OMNeT++ IDE  
3. Build project (ensure HdMapPacket.msg compiles correctly)  
4. Run configuration: simulations/NR/cars/HdMapSumoProject.ini

---

## TCP Communication Flow

1. Vehicle initializes and creates TCP socket  
2. TCP 3-way handshake establishes connection  
3. Vehicle sends HdMapPacket request  
4. Server processes request and sends response  
5. Optional graceful connection termination  

---

## Configuration Parameters (INI)

Typical configurable parameters:

- localPort  
- connectAddress  
- connectPort  
- requestInterval  
- packetLength  
- numApps  
- hasTcp = true  

Example:

*.car[*].numApps = 1  
*.car[*].app[0].typename = "HdMapCarApp"  
*.server.numApps = 1  
*.server.app[0].typename = "HdMapServerApp"  

---

## Evaluation Metrics

- End-to-end latency (request → response)  
- TCP throughput  
- Congestion impact under load  
- Packet retransmission behavior  
- Scalability with multiple vehicles  
- Connection stability under mobility  

Results can be extracted via OMNeT++ .sca and .vec files and analyzed using Python, MATLAB, or Excel.

---

## Future Improvements

- Dynamic HD map tile modeling  
- Multi-vehicle stress scenarios  
- Adaptive request rates  
- MEC offloading scenario extension  
- Structured CSV export for performance comparison  

---

## Author

Ukamaka Akumili Anaedu  
Automation & Embedded Systems Engineer  
Connected Mobility & Network Simulation Research  
