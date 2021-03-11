#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/queue.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-routing-helper.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("FirstScriptExample");
int main(int argc, char *argv[])
{
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);
    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    NodeContainer nodes;
    nodes.Create(5);
    //NodeContainer n01 = NodeContainer (nodes.Get (0), nodes.Get (1));
    //NodeContainer n12 = NodeContainer (nodes.Get (1), nodes.Get (2));
    PointToPointHelper pointToPoint, pointToPoint1, pointToPoint2, pointToPoint3, pointToPoint4, pointToPoint5;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("10ms"));

    pointToPoint1.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint1.SetChannelAttribute("Delay", StringValue("7ms"));

    pointToPoint2.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
    pointToPoint2.SetChannelAttribute("Delay", StringValue("15ms"));

    pointToPoint3.SetDeviceAttribute("DataRate", StringValue("15Mbps"));
    pointToPoint3.SetChannelAttribute("Delay", StringValue("10ms"));

    pointToPoint4.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    pointToPoint4.SetChannelAttribute("Delay", StringValue("20ms"));

    pointToPoint5.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    pointToPoint5.SetChannelAttribute("Delay", StringValue("1ms"));

    NetDeviceContainer devices;
    NetDeviceContainer nd01 = pointToPoint.Install(nodes.Get(0), nodes.Get(1));
    NetDeviceContainer nd12 = pointToPoint1.Install(nodes.Get(1), nodes.Get(2));
    NetDeviceContainer nd02 = pointToPoint2.Install(nodes.Get(0), nodes.Get(2));
    NetDeviceContainer nd13 = pointToPoint3.Install(nodes.Get(1), nodes.Get(3));
    NetDeviceContainer nd23 = pointToPoint4.Install(nodes.Get(2), nodes.Get(3));
    NetDeviceContainer nd34 = pointToPoint5.Install(nodes.Get(3), nodes.Get(4));

    InternetStackHelper stack;
    stack.Install(nodes);
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i1 = address.Assign(nd01);
    Ipv4AddressHelper address1;
    address1.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i2 = address.Assign(nd12);
    Ipv4AddressHelper address2;
    address2.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer i3 = address.Assign(nd02);
    Ipv4AddressHelper address3;
    address3.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i4 = address.Assign(nd13);
    Ipv4AddressHelper address4;
    address4.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i5 = address.Assign(nd23);
    Ipv4AddressHelper address5;
    address5.SetBase("10.1.6.0", "255.255.255.0");
    Ipv4InterfaceContainer i6 = address.Assign(nd34);

    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(4));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));
    UdpEchoClientHelper echoClient(i6.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(5));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
    AnimationInterface anim("Wheatstone1.xml");

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
