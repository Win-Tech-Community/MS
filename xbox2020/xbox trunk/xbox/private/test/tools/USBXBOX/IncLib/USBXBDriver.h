/*++

Copyright (c) 2000  Microsoft Corporation

Module Name:

    USBXBDriver.h

Abstract:

    header of exposed routines from the SliXbox driver

Author:

    Jason Gould (a-jasgou) July 2000

--*/
#ifndef __slixdriver_h__
#define __slixdriver_h__

#define _IN
#define _OUT
#define _OPT


typedef long USBD_STATUS;
typedef unsigned char       BYTE;
typedef unsigned long		DWORD;

#ifdef __cplusplus
extern "C" { //to prevent name mangling... 
#endif

/*************************************************************************************
Function:   SlixdIn
Purpose:	create & send an IN packet, receive the data, return any errors
Params:     in Address --- the topology of the device to receive from (see PORT_FROM_ADDRESS above)
			in Endpoint --- the endpoint of the device to receive from 
			out data --- pointer to the buffer to receive data
			in out len --- pointer to max length of data buffer, receives size of data received
Return:     a USBD_STATUS code indicating error or success.
*************************************************************************************/
USBD_STATUS SlixdIn(_IN BYTE Port,_IN BYTE Slot, _IN BYTE InterfaceNumber, _IN BYTE Endpoint, _OUT char * data, _IN _OUT DWORD * len);


/*************************************************************************************
Function:   SlixdOut
Purpose:	create & send an OUT packet, send the data, return any errors
Params:     in Address --- the topology of the device to send to (see PORT_FROM_ADDRESS above)
			in Endpoint --- the endpoint of the device to send to
			in data --- pointer to the buffer to receive data
			in len --- number of bytes to send
Return:     a USBD_STATUS code indicating error or success.
*************************************************************************************/
USBD_STATUS SlixdOut(_IN BYTE Port,_IN BYTE Slot, _IN BYTE InterfaceNumber, _IN BYTE Endpoint, _IN char * data, _IN DWORD len);


/*************************************************************************************
Function:   SlixdSetup
Purpose:	create & send a SETUP packet, send the data, return any errors
note: more stuff may be needed to receive or send additional data...
Params:     in Address --- the topology of the device to send to (see PORT_FROM_ADDRESS above)
			in Endpoint --- the endpoint of the device to send to
			in data --- pointer to the buffer to receive data
			in len --- number of bytes to send
			data2 --- pointer to buffer to receive or send data. OPT if data[6]==0
			len2 --- p to length of data2 if sending, p to max length if receiving, & 
				will receive length of data received.  OPT if data[6] == 0
Return:     a USBD_STATUS code indicating error or success.
*************************************************************************************/
USBD_STATUS SlixdSetup(_IN BYTE Port,_IN BYTE Slot, _IN BYTE InterfaceNumber, _IN BYTE Endpoint, _IN char * data, _IN DWORD len, 
					   _OPT _IN _OUT char * data2, _OPT _IN _OUT USHORT *len2);


USBD_STATUS SlixdReset(_IN BYTE Port,_IN BYTE Slot, _IN BYTE InterfaceNumber);



#ifdef __cplusplus
} //extern "C"
#endif


#endif