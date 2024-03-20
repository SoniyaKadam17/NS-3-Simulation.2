Wi-Fi Networks
In this laboratory assignment, you will work on the simulation of WiFi Networks:
• Before starting, you need to read Section 7.3 in the ns-3 Tutorial available in Canvas (Module
“Laboratory Assignments”)
• Note that here are three models available for WiFi MAC, namely, Access Point (AP)
(ns3::ApWifiMac), non-AP Station (STA) (ns3::StaWifiMac), and Ad hoc network
(ns3::AdhocWifiMac).
• For more information about the WiFi model in ns3, visit the user documentation for the WiFi module:
https://www.nsnam.org/docs/release/3.39/models/html/wifi.html
• For more details about the API documentation page for the WiFi model, visit ns-3 Doxygen:
https://www.nsnam.org/docs/doxygen/df/d5e/group__wifi.html
Please use the report template available in the “Laboratory Assignments” module to prepare the
report with your solution to this assignment.
Submission materials:
1. Prepare a brief report following the report template in Canvas (add the answer the questions
included in each Task):
• Task 1:
o Experimental setup: Explain the key lines of your code that you have modified to
implement the specific network.
o Results: Comment and include screenshot(s) of the packet traces in Wireshark
and the simulation results with and without RTS/CTS.
Answer the questions at the end of Task 1. When needed include screenshots
that support your answers.
o Conclusions: what did you learn?
• Task 2:
o Experimental setup: Explain the key lines of your code that you have modified to
implement the specific network.
o Results: Comment and include screenshot(s) of the packet traces in Wireshark
and the simulation results with and without RTS/CTS.
Answer the questions at the end of Task 2. When needed include screenshots
that support your answers.
o Conclusions: what did you learn?
2. In your submission, include also your modified .cc files.=
Remember: the laboratory assignments can be conducted either individually or in couples. If you want to
work in couples, only one of the team members will need to submit the assignment.
Task 1: Wireless Local Area Network – Ad-hoc Mode (55 points)
Define a Wireless Local Area Network (WLAN) operating in Ad-hoc Mode with 5 nodes. Nodes move by
following a 2D random walk in a rectangular area defined by the lower-left corner (x=-90 m, y=-90 m) and
the upper-right corner (x=90 m, y=90 m).
TIP: Change third.cc so your network only has Wifi nodes of type ns3::AdhocWiFiMac. Remove any
parameter not defined for ns3::AdhocWiFiMac.
TIP: Remember that we do not want a constant position mobility model.
Consider the following specifications:
• Channel: Default wireless channel in ns-3
• Physical Layer:
o Default parameters in IEEE 802.11ac standard
TIP: Check the user documentation, method SetStandard of WifiHelper
• Link Layer:
o Standard MAC without quality of service control
o Remember: the network should operate in ad-hoc mode
• Network Layer:
o Standard IPv4
o Address range: 192.168.1.0/24
o Assume that all the nodes behave as ideal routers and can exchange their routing tables
in the background
• Transport Layer:
o UDP
• Application Layer:
o UDP Echo Server at Node 0:
▪ Listening on port 20
o UDP Echo Client at Node 3:
▪ Sends 2 UDP Echo packets to the server at times 1s and 2s
o UDP Echo Client at Node 4:
▪ Sends 2 UDP Echo packets to the server at times 2s and 4s
o Packet size: 512 bytes
• Additional parameters:
o Set up a packet tracer ONLY on Node 1
Answer the following questions:
• Are all the frames acknowledged? Explain why.
• Are there any collisions in the network? Explain why. How have you reached this conclusion?
• How can the nodes be forced to utilize the RTS/CTS handshake procedure?
• Force the utilization of RTS/CTS in the network:
TIP: In the ns-3 Doxygen, check the attributes of ns3::WifiRemoteStationManager. In the”Detailed
Description”, look for an attribute used for this purpose.
o Are there any collisions in data frames now?
o Which is the benefit or RTS/CTS? Briefly explain how RTS/CTS works.
o Where can you find the Network Allocation Vector information?
Task 2: Wireless LAN – Infrastructure Mode (45 points)
Define a Wireless Local Area Network (LAN) operating in Infrastructure Mode with 5 nodes and 1
access point. Nodes move by following a 2D random walk in a rectangular area defined by the lower-left
corner (x=-90 m, y=-90 m) and the upper-right corner (x=90 m, y=90 m). The network name (SSID) should
be EECE5155. To start, do not force the RTS/CTS handshaking process. Consider the following
specifications:
• Channel: Default wireless channel in ns-3
• Physical Layer:
o Default parameters in IEEE 802.11ac standard
• Link Layer:
o Standard MAC without quality of service control
o Remember: the network should operate in infrastructure mode
• Network Layer:
o Standard IPv4
o Address range: 192.168.2.0/24
o Assume that all the nodes behave as ideal routers and can exchange their routing tables
in the background
• Transport Layer:
o UDP
• Application Layer:
o UDP Echo Server at Node 0:
▪ Listening on port 21
o UDP Echo Client at Node 3:
▪ Sends 2 UDP Echo packets to the server at times 3s and 5s
o UDP Echo Client at Node 4:
▪ Sends 2 UDP Echo packets to the server at times 2s and 5s
o Packet size: 512 bytes
• Additional parameters:
o Set up a packet tracer ONLY on Node 4 (one of the clients) and on the AP.
Answer the following questions:
• Explain the behavior of the AP. What is happening since the very first moment the network starts
operating?
• Take a look to a beacon frame. Which are the most relevant parameters defined in it?
• Are there any collisions in the network? When are these collisions happening?
• As in Task 1, force the utilization of the RTS/CTS handshaking process and repeat the
simulation. Are there any collisions in data frames now? Explain why
