# HD-Map-V2X-Messaging-in-Simu5G-OMNeT-
A simulation project that models bi-directional message exchange between connected vehicles and an HD Map server using OMNeT++ (6) and Simu5G.
The goal is to evaluate how well a vehicle can request map updates / send telemetry and receive HD map responses under different network and traffic conditions.


Overview

Modern autonomous and connected vehicles rely on High Definition (HD) Maps for:

lane-level localization

curvature and geometry awareness

road events (construction, speed updates, hazards)

path planning refinement

Unlike lightweight UDP beacons, HD map delivery requires:

reliability

ordered delivery

congestion control

connection management

This project implements that using TCP sessions between vehicle nodes and an HD Map server node inside a 5G simulation scenario.

System Architecture

Vehicle (Client) ↔ 5G NR Network ↔ HD Map Server (TCP)

HdMapCarApp
Initiates TCP connection and sends structured map requests.

HdMapServerApp
Listens on TCP port, accepts connections, processes requests, and returns map data.

HdMapPacket.msg
Defines the custom application-level message structure.
