/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

// Default Network Topology
//
// 192.168.1.0/255.255.255.0
//                 
//  *    *    *    *    *
//  |    |    |    |    |   
// n4   n3   n2   n1    n0 
//
//
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Assignment2Task1");//defining a new log component named "Assignment1Task1".

int
main(int argc, char* argv[])
{
    bool verbose = true;
    uint32_t nWifi = 5; // number of nodes is 5
    bool tracing = true;

   Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue (0));// RTS/CTS 

    CommandLine cmd(__FILE__);
    cmd.AddValue("nWifi", "Number of wifi STA devices", nWifi);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
    cmd.AddValue("tracing", "Enable pcap tracing", tracing);

    cmd.Parse(argc, argv);

    // The underlying restriction of 18 is due to the grid position
    // allocator's configuration; the grid layout will exceed the
    // bounding box if more than 18 nodes are provided.
    if (nWifi > 18)
    {
        std::cout << "nWifi should be 18 or less; otherwise grid layout exceeds the bounding box"
                  << std::endl;
        return 1;
    }

    if (verbose) // Enable logging at the INFO level for the log components 
    {
        LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }
    NodeContainer wifiAdhocNodes;
    wifiAdhocNodes.Create(nWifi);//Creating WIfi container

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    Ssid ssid = Ssid("ns-3-ssid");//Setting up SSID
        
    WifiHelper wifi;

    NetDeviceContainer AdhocDevices;// Wifi nodes charactersitic 
    mac.SetType("ns3::AdhocWifiMac");
    AdhocDevices = wifi.Install(phy, mac, wifiAdhocNodes);


    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX",
                                  DoubleValue(0.0),
                                  "MinY",
                                  DoubleValue(0.0),
                                  "DeltaX",
                                  DoubleValue(5.0),
                                  "DeltaY",
                                  DoubleValue(10.0),
                                  "GridWidth",
                                  UintegerValue(3),
                                  "LayoutType",
                                  StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                             "Bounds",
                              RectangleValue(Rectangle(-90, 90, -90, 90)));// grid specifications
    mobility.Install(wifiAdhocNodes);


    InternetStackHelper stack;
    stack.Install(wifiAdhocNodes);

    Ipv4AddressHelper address;
    Ipv4InterfaceContainer WifiInterfaces;
    address.SetBase("192.168.1.0", "255.255.255.0");// Setting IP address of the wifi devices
    address.Assign(AdhocDevices);// Assigning IP address of the wifi devices
    WifiInterfaces = address.Assign(AdhocDevices);

    UdpEchoServerHelper echoServer(20);// sets the listening port to 20

    ApplicationContainer serverApps = echoServer.Install(wifiAdhocNodes.Get(0)); // Echoing to server with index 0
    serverApps.Start(Seconds(1.0));// start time
    serverApps.Stop(Seconds(10.0));// stop time

    UdpEchoClientHelper echoClient1(WifiInterfaces.GetAddress(0), 20);// specifies the destination address and port number for the echo client.
    echoClient1.SetAttribute("MaxPackets", UintegerValue(2));// sending 2 packet
    echoClient1.SetAttribute("Interval", TimeValue(Seconds(1.0)));// packet at interval of 1 second
    echoClient1.SetAttribute("PacketSize", UintegerValue(512));// size of the packets is 512 bytes

    ApplicationContainer clientApps1 = echoClient1.Install(wifiAdhocNodes.Get(3));// client node transmitting 3
    clientApps1.Start(Seconds(1.0));// start time
    clientApps1.Stop(Seconds(10.0));// stop time

    UdpEchoClientHelper echoClient2(WifiInterfaces.GetAddress(0), 20);// specifies the destination address and port number for the echo client.
    echoClient2.SetAttribute("MaxPackets", UintegerValue(2));// sending 2 packet
    echoClient2.SetAttribute("Interval", TimeValue(Seconds(2.0)));// packet at interval of 2 second
    echoClient2.SetAttribute("PacketSize", UintegerValue(512));// size of the packets is 512 bytes

    ApplicationContainer clientApps2 = echoClient2.Install(wifiAdhocNodes.Get(4));// client node transmitting 4 
    clientApps2.Start(Seconds(2.0));// start time
    clientApps2.Stop(Seconds(10.0));// stop time

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(10.0));
    if (tracing)
    {
    phy.SetPcapDataLinkType(WifiPhyHelper::DLT_IEEE802_11_RADIO);
    phy.EnablePcap("Assignment2Task1", AdhocDevices.Get(1)); // creating Pcap file of the node 1
    }
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}