#include <iostream>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define ADDRESS "127.0.0.1"
#define PORT 9000

#define OUTPUT_BUFFER_SIZE 1024
#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <Psapi.h>
#include "Utils.hpp"
using std::string;

#pragma warning(disable : 4996)


#include <tchar.h>


void SendOSCMessage(const char * arg)
{
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/chatbox/input" ) 
            << arg << true << osc::EndMessage
        << osc::EndBundle;
    
    transmitSocket.Send( p.Data(), p.Size() );
}

void SendSpotify()
{
    while (true)
    {
        string thing =
                GetSpotify() +
                " || Made in C++";
        //std::cout << thing << endl;
        //    const char* sex = thing.c_str();
        // std::cout << sex << endl;
        std::cout << thing << endl;
        SendOSCMessage(thing.c_str());
        Sleep(1500);
        
    }
}

void SendTabbed()
{
    while (true)
    {
        auto joe = "Tabbed Into: " + GetFocused() + " || Made in C++";
        SendOSCMessage( joe.c_str());
        Sleep(1500);
    }
}

int main(int argc, char* argv[])
{
    Menu:
    
    std::cout << "1. Spotify || 2. Tabbed in"
    << endl;
    char outinput;
    
    std::cin >> outinput;
    int joe = (char)outinput;
    switch (outinput)
    {
        case '1':
            SendSpotify();
        break; 
        case '2':
            SendTabbed();
        break;
        default:
            system("CLS");
            std::cout << "Enter Valid Input Please :)" << endl;
            goto Menu;
            break;
            
            
    }
}
