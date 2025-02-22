//------------------------------------------------------------------------------
// <copyright file="SocketOptionName.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>                                                                
//------------------------------------------------------------------------------

namespace System.Net.Sockets {
    using System;

    //
    // Option names per-socket.
    //

    /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName"]/*' />
    /// <devdoc>
    ///    <para>
    ///       Defines socket option names for the <see cref='System.Net.Sockets.Socket'/> class.
    ///    </para>
    /// </devdoc>
    //UEUE
    public enum SocketOptionName {

        //
        // good for SocketOptionLevel.Socket
        //

        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Debug"]/*' />
        /// <devdoc>
        ///    <para>Record debugging information.</para>
        /// </devdoc>
        Debug                   = 0x0001,           // turn on debugging info recording 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.AcceptConnection"]/*' />
        /// <devdoc>
        ///    <para>Socket is listening.</para>
        /// </devdoc>
        AcceptConnection        = 0x0002,           // socket has had listen() 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ReuseAddress"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Allows the socket to be bound to an address that is already in use.
        ///    </para>
        /// </devdoc>
        ReuseAddress            = 0x0004,           // allow local address reuse 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.KeepAlive"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Send keep-alives.
        ///    </para>
        /// </devdoc>
        KeepAlive               = 0x0008,           // keep connections alive 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.DontRoute"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Do not route, send directly to interface addresses.
        ///    </para>
        /// </devdoc>
        DontRoute               = 0x0010,           // just use interface addresses 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Broadcast"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Permit sending broadcast messages on the socket.
        ///    </para>
        /// </devdoc>
        Broadcast               = 0x0020,           // permit sending of broadcast msgs 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.UseLoopback"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Bypass hardware when possible.
        ///    </para>
        /// </devdoc>
        UseLoopback             = 0x0040,           // bypass hardware when possible 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Linger"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Linger on close if unsent data is present.
        ///    </para>
        /// </devdoc>
        Linger                  = 0x0080,           // linger on close if data present 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.OutOfBandInline"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Receives out-of-band data in the normal data stream.
        ///    </para>
        /// </devdoc>
        OutOfBandInline         = 0x0100,           // leave received OOB data in line 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.DontLinger"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Close socket gracefully without lingering.
        ///    </para>
        /// </devdoc>
        DontLinger              = ~Linger,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ExclusiveAddressUse"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Enables a socket to be bound for exclusive access.
        ///    </para>
        /// </devdoc>
        ExclusiveAddressUse     = ~ReuseAddress,    // disallow local address reuse
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.SendBuffer"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Specifies the total per-socket buffer space reserved for sends. This is
        ///       unrelated to the maximum message size or the size of a TCP window.
        ///    </para>
        /// </devdoc>
        SendBuffer              = 0x1001,           // send buffer size
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ReceiveBuffer"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Send low water mark.
        ///    </para>
        /// </devdoc>
        ReceiveBuffer           = 0x1002,           // receive buffer size
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.SendLowWater"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Specifies the total per-socket buffer space reserved for receives. This is unrelated to the maximum message size or the size of a TCP window.
        ///    </para>
        /// </devdoc>
        SendLowWater            = 0x1003,           // send low-water mark
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ReceiveLowWater"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Receive low water mark.
        ///    </para>
        /// </devdoc>
        ReceiveLowWater         = 0x1004,           // receive low-water mark
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.SendTimeout"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Send timeout.
        ///    </para>
        /// </devdoc>
        SendTimeout             = 0x1005,           // send timeout
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ReceiveTimeout"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Receive timeout.
        ///    </para>
        /// </devdoc>
        ReceiveTimeout         = 0x1006,           // receive timeout 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Error"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Get error status and clear.
        ///    </para>
        /// </devdoc>
        Error                   = 0x1007,          // get error status and clear 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Type"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Get socket type.
        ///    </para>
        /// </devdoc>
        Type                    = 0x1008,           // get socket type 
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.MaxConnections"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Maximum queue length that can be specified by <see cref='System.Net.Sockets.Socket.Listen'/>.
        ///    </para>
        /// </devdoc>
        MaxConnections          = 0x7fffffff,       // Maximum queue length specifiable by listen.


        //
        // the following values are taken from ws2tcpip.h,
        // note that these are understood only by ws2_32.dll and are not backwards compatible
        // with the values found in winsock.h which are understood by wsock32.dll.
        //

        //
        // good for SocketOptionLevel.IP
        //

        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.IPOptions"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP options.
        ///    </para>
        /// </devdoc>
        IPOptions               = 1,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.HeaderIncluded"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Header is included with data.
        ///    </para>
        /// </devdoc>
        HeaderIncluded          = 2,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.TypeOfService"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP type of service and preced.
        ///    </para>
        /// </devdoc>
        TypeOfService           = 3,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.IpTimeToLive"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP time to live.
        ///    </para>
        /// </devdoc>
        IpTimeToLive            = 4,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.MulticastInterface"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP multicast interface.
        ///       - Additional comments by mbolien:
        ///         multicast interface  You provide it with an SOCKADDR_IN, and that tells the 
        ///         system that it should receive multicast messages on that interface (if you 
        ///         have more than one interface).  Binding the socket is not sufficient, since 
        ///         if the Ethernet hardware isn�t set up to grab the multicast packets, it won�t 
        ///         do good to bind the socket.  Kinda like raw sockets.  Unless you 
        ///         put the Ethernet card in promiscuous mode, you�ll only get stuff sent to and 
        ///         from your machine.
        ///    </para>
        /// </devdoc>
        MulticastInterface      = 9,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.MulticastTimeToLive"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP multicast time to live.
        ///    </para>
        /// </devdoc>
        MulticastTimeToLive     = 10,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.MulticastLoopback"]/*' />
        /// <devdoc>
        ///    <para>
        ///       IP Multicast loopback.
        ///    </para>
        /// </devdoc>
        MulticastLoopback       = 11,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.AddMembership"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Add an IP group membership.
        ///    </para>
        /// </devdoc>
        AddMembership           = 12,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.DropMembership"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Drop an IP group membership.
        ///    </para>
        /// </devdoc>
        DropMembership          = 13,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.DontFragment"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Don't fragment IP datagrams.
        ///    </para>
        /// </devdoc>
        DontFragment            = 14,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.AddSourceMembership"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Join IP group/source.
        ///    </para>
        /// </devdoc>
        AddSourceMembership     = 15,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.DropSourceMembership"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Leave IP group/source.
        ///    </para>
        /// </devdoc>
        DropSourceMembership    = 16,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.BlockSource"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Block IP group/source.
        ///    </para>
        /// </devdoc>
        BlockSource             = 17,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.UnblockSource"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Unblock IP group/source.
        ///    </para>
        /// </devdoc>
        UnblockSource           = 18,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.PacketInformation"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Receive packet information for ipv4.
        ///    </para>
        /// </devdoc>
        PacketInformation       = 19,



        //
        // good for SocketOptionLevel.Tcp
        //

        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.NoDelay"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Disables the Nagle algorithm for send coalescing.
        ///    </para>
        /// </devdoc>
        NoDelay                 = 1,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.BsdUrgent"]/*' />
        /// <devdoc>
        ///    <para>[To be supplied.]</para>
        /// </devdoc>
        BsdUrgent               = 2,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.Expedited"]/*' />
        Expedited               = 2,


        //
        // good for SocketOptionLevel.Udp
        //

        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.NoChecksum"]/*' />
        /// <devdoc>
        ///    <para>[To be supplied.]</para>
        /// </devdoc>
        NoChecksum              = 1,
        /// <include file='doc\SocketOptionName.uex' path='docs/doc[@for="SocketOptionName.ChecksumCoverage"]/*' />
        /// <devdoc>
        ///    <para>
        ///       Udp-Lite checksum coverage.
        ///    </para>
        /// </devdoc>
        ChecksumCoverage        = 20,

    }; // enum SocketOptionName


} // namespace System.Net.Sockets
