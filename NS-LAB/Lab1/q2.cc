
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/queue.h"
#include "ns3/drop-tail-queue.h"
// Default Network Topology
//
// 10.1.1.0
// n0 -------------- n1-------n2
// point-to-point
//

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
int
main (int argc, char *argv[])
{​​​​​​​​
CommandLine cmd (__FILE__);
cmd.Parse (argc, argv);

Time::SetResolution (Time::NS);
LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
NodeContainer nodes;
nodes.Create (3);
//NodeContainer n01 = NodeContainer (nodes.Get (0), nodes.Get (1));
//NodeContainer n12 = NodeContainer (nodes.Get (1), nodes.Get (2));
PointToPointHelper pointToPoint;
//pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
pointToPoint.SetQueue("ns3::DropTailQueue","MaxSize",StringValue ("50p"));

NetDeviceContainer devices;
NetDeviceContainer nd01 = pointToPoint.Install (nodes.Get (0), nodes.Get (1));
NetDeviceContainer nd12 = pointToPoint.Install (nodes.Get (1), nodes.Get (2));

InternetStackHelper stack;
stack.Install (nodes);
Ipv4AddressHelper address;
address.SetBase ("10.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer i1 = address.Assign (nd01);
Ipv4AddressHelper address1;
address1.SetBase ("10.1.2.0", "255.255.255.0");
Ipv4InterfaceContainer i2 = address.Assign (nd12);
UdpEchoServerHelper echoServer (9);
ApplicationContainer serverApps = echoServer.Install (nodes.Get (2));
serverApps.Start (Seconds (1.0));
serverApps.Stop (Seconds (10.0));
UdpEchoClientHelper echoClient (i2.GetAddress (1), 9);
echoClient.SetAttribute ("MaxPackets", UintegerValue (5));
echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.25)));
echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
clientApps.Start (Seconds (2.0));
clientApps.Stop (Seconds (10.0));
AsciiTraceHelper ascii;
pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("myfirst.tr"));

Simulator::Run ();
Simulator::Destroy ();
return 0;
}​​​​​​​​
// sudo ./waf --run "scratch/lab1_2_180953212 --ns3::PointToPointNetDevice::DataRate=50Mbps"

