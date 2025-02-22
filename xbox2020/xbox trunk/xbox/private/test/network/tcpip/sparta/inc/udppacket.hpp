/****************************************************************************************
*                                    SPARTA project                                     *
*                                                                                       *
* (TCP/IP test team)                                                                    *
*                                                                                       *
* Filename: UDPPacket.hpp                                                               *
* Description: this defines the UDP Packet class , extends the IP Packet                *
*               class                                                                   *
*                                                                                       *
* Revision history:     name          date         modifications                        *
*                                                                                       *
*                       balasha      3/20/2000    created                               *
*                       jbekmann      5/31/2000    made destructor virtual              *
*                                                                                       *
*                                                                                       *
*                (C) Copyright Microsoft Corporation 1999-2000                          *
*****************************************************************************************/


#ifndef __SPARTA_UDP_PACKET_H__
#define __SPARTA_UDP_PACKET_H__

#include "sparta.h"
#include "udp.h"
#include "IPHeader.hpp"
#include "Packet.hpp"
#include "UDPHeader.hpp"
#include "IPPacket.hpp"


class CUDPPacket : public CIPPacket
{

public:
    CUDPHeader &UDPHeader;

    CUDPPacket(MAC_MEDIA_TYPE MediaType, BOOL IsVersion6 = FALSE);
    CUDPPacket(PKT_PACKET Packet, CMacHeader &MacHeaderParam, 
               CIPHeader &IPHeader, CUDPHeader &UDPHeader, BOOL IsVersion6 = FALSE);
    SPARTA_STATUS PreparePacketForSend();
    USHORT CalcChecksum();
    virtual ~CUDPPacket();

    virtual int GetPacketType();

    virtual void PrintPacket();

};

#endif //__SPARTA_UDP_PACKET_H__
