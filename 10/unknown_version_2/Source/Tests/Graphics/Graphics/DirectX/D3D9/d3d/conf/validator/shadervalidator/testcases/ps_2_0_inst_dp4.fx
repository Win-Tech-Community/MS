ted:
    NDIS_STATUS SetData(
        _In_ PVOID  pInformationBuffer,
        _In_ UINT   InformationBufferLength,
        _In_ PUINT  pBytesRead,
        _In_ PUINT  pBytesNeeded );
};

class CGetPmParametersJob : public CSimpleQueryOidJob
{
public:
    CGetPmParametersJob(
        _In_ WFC_ACTIVITY_ID ActivityId ) 
            : CSimpleQueryOidJob(ActivityId) 
    {
    };

    ~CGetPmParametersJob()
    {
    };

protected:
    NDIS_STATUS QueryData(
            _In_ PVOID  pInformationBuffer,
            _In_ UINT   InformationBufferLength,
            _In_ PUINT  pBytesWritten,
            _In_ PUINT  pBytesNeeded );
};


/*****************************************************************************
 * miniport.cpp - UART miniport implementation
 *****************************************************************************
 * Copyright (c) Microsoft.  All rights reserved.
 *
 */

#pragma warning (disable : 4100 4127)

#include "private.h"
#include "ksdebug.h"

#define STR_MODULENAME "UartMini: "


#pragma code_seg("PAGE")
/*****************************************************************************
 * PinDataRangesStream
 *****************************************************************************
 * Structures indicating range of valid format values for streaming pins.
 */
static
KSDATARANGE_MUSIC PinDataRangesStream[] =
{
    {
        {
            sizeof(KSDATARANGE_MUSIC),
            0,
            0,
            0,
            STATICGUIDOF(KSDATAFORMAT_TYPE_MUSIC),
            STATICGUIDOF(KSDATAFORMAT_SUBTYPE_MIDI),
            STATICGUIDOF(KSDATAFORMAT_SPECIFIER_NONE)
        },
        STATICGUIDOF(KSMUSIC_TECHNOLOGY_PORT),
        0,
        0,
        0xFFFF
    }
};

/*****************************************************************************
 * PinDataRangePointersStream
 *****************************************************************************
 * List of pointers to structures indicating range of valid format values
 * for live pins.
 */
static
PKSDATARANGE PinDataRangePointersStream[] =
{
    PKSDATARANGE(&PinDataRangesStream[0])
};

/*****************************************************************************
 * PinDataRangesBridge
 *****************************************************************************
 * Structures indicating range of valid format values for bridge pins.
 */
static
KSDATARANGE PinDataRangesBridge[] =
{
   {
      sizeof(KSDATARANGE),
      0,
      0,
      0,
      STATICGUIDOF(KSDATAFORMAT_TYPE_MUSIC),
      STATICGUIDOF(KSDATAFORMAT_SUBTYPE_MIDI_BUS),
      STATICGUIDOF(KSDATAFORMAT_SPECIFIER_NONE)
   }
};

/*****************************************************************************
 * PinDataRangePointersBridge
 *****************************************************************************
 * List of pointers to structures indicating range of valid format values
 * for bridge pins.
 */
static
PKSDATARANGE PinDataRangePointersBridge[] =
{
    &PinDataRangesBridge[0]
};

#define kMaxNumCaptureStreams       1
#define kMaxNumRenderStreams        1

/*****************************************************************************
 * MiniportPins
 *****************************************************************************
 * List of pins.
 */
static
PCPIN_DESCRIPTOR MiniportPins[] =
{
    {
        kMaxNumRenderStreams,kMaxNumRenderStreams,0,  // InstanceCount
        NULL,   // AutomationTable
        {       // KsPinDescriptor
            0,                                          // InterfacesCount
            NULL,                                       // Interfaces
            0,                                          // MediumsCount
            NULL,                                       // Mediums
            SIZEOF_ARRAY(PinDataRangePointersStream),   // DataRangesCount
            PinDataRangePointersStream,                 // DataRanges
            KSPIN_DATAFLOW_IN,                          // DataFlow
            KSPIN_COMMUNICATION_SINK,                   // Communication
            (GUID *) &KSCATEGORY_AUDIO,                 // Category
            &KSAUDFNAME_MIDI,                           // Name
            0                                           // Reserved
        }
    },
    {
        0,0,0,  // InstanceCount
        NULL,   // AutomationTable
        {       // KsPinDescriptor
            0,                                          // InterfacesCount
            NULL,                                       // Interfaces
            0,                                          // MediumsCount
            NULL,                                       // Mediums
            SIZEOF_ARRAY(PinDataRangePointersBridge),   // DataRangesCount
            PinDataRangePointersBridge,                 // DataRanges
            KSPIN_DATAFLOW_OUT,                         // DataFlow
            KSPIN_COMMUNICATION_NONE,                   // Communication
            (GUID *) &KSCATEGORY_AUDIO,                 // Category
            NULL,                                       // Name
            0                                           // Reserved
        }
    },
    {
        kMaxNumCaptureStreams,kMaxNumCaptureStreams,0,  // InstanceCount
        NULL,   // AutomationTable
        {       // KsPinDescriptor
            0,                                          // InterfacesCount
            NULL,                                       // Interfaces
            0,                                          // MediumsCount
            NULL,                                       // Mediums
            SIZEOF_ARRAY(PinDataRangePointersStream),   // DataRangesCount
            PinDataRangePointersStream,                 // DataRanges
            KSPIN_DATAFLOW_OUT,                         // DataFlow
            KSPIN_COMMUNICATION_SINK,                   // Communication
            (GUID *) &KSCATEGORY_AUDIO,                 // Category
            &KSAUDFNAME_MIDI,                           // Name
            0                                           // Reserved
        }
    },
    {
        0,0,0,  // InstanceCount
        NULL,   // AutomationTable
        {       // KsPinDescriptor
            0,                                          // InterfacesCount
            NULL,                                       // Interfaces
            0,                                          // MediumsCount
            NULL,                                       // Mediums
            SIZEOF_ARRAY(PinDataRangePointersBridge),   // DataRangesCount
            PinDataRangePointersBridge,                 // DataRanges
            KSPIN_DATAFLOW_IN,                          // DataFlow
            KSPIN_COMMUNICATION_NONE,                   // Communication
            (GUID *) &KSCATEGORY_AUDIO,                 // Category
            NULL,                                       // Name
            0                                           // Reserved
        }
    }
};

/*****************************************************************************
 * MiniportConnections
 *****************************************************************************
 * List of connections.
 */
static
PCCONNECTION_DESCRIPTOR MiniportConnections[] =
{
    { PCFILTER_NODE,  0,  PCFILTER_NODE,    1 },
    { PCFILTER_NODE,  3,  PCFILTER_NODE,    2 }    
};

/*****************************************************************************
 * MiniportFilterDescriptor
 *****************************************************************************
 * Complete miniport filter description.
 */
static
PCFILTER_DESCRIPTOR MiniportFilterDescriptor =
{
    0,                                  // Version
    NULL,                               // AutomationTable
    sizeof(PCPIN_DESCRIPTOR),           // PinSize
    SIZEOF_ARRAY(MiniportPins),         // PinCount
    MiniportPins,                       // Pins
    sizeof(PCNODE_DESCRIPTOR),          // NodeSize
    0,                                  // NodeCount
    NULL,                               // Nodes
    SIZEOF_ARRAY(MiniportConnections),  // ConnectionCount
    MiniportConnections,                // Connections
    0,                                  // CategoryCount
    NULL                                // Categories
};

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::GetDescription()
 *****************************************************************************
 * Gets the topology.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiUart::
GetDescription
(
    OUT     PPCFILTER_DESCRIPTOR *  OutFilterDescriptor
)
{
    PAGED_CODE();

    ASSERT(OutFilterDescriptor);

    _DbgPrintF(DEBUGLVL_VERBOSE,("GetDescription"));

    *OutFilterDescriptor = &MiniportFilterDescriptor;

    return STATUS_SUCCESS;
}


#pragma code_seg("PAGE")
/*****************************************************************************
 * CreateMiniportMidiUart()
 *****************************************************************************
 * Creates a MPU-401 miniport driver for the adapter.  This uses a
 * macro from STDUNK.H to do all the work.
 */
_When_((PoolType&NonPagedPoolMustSucceed)!=0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
                      "Allocation failures cause a system crash"))
NTSTATUS
CreateMiniportMidiUart
(
    OUT     PUNKNOWN *  Unknown,
    IN      REFCLSID,
    IN      PUNKNOWN    UnknownOuter    OPTIONAL,
    IN      POOL_TYPE   PoolType
)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB,("CreateMiniportDMusUART"));
    ASSERT(Unknown);

    STD_CREATE_BODY_(   CMiniportMidiUart,
                        Unknown,
                        UnknownOuter,
                        PoolType, 
                        PMINIPORTMIDI);
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::ProcessResources()
 *****************************************************************************
 * Processes the resource list, setting up helper objects accordingly.
 */
NTSTATUS
CMiniportMidiUart::
ProcessResources
(
    IN      PRESOURCELIST   ResourceList
)
{
    PAGED_CODE();
    _DbgPrintF(DEBUGLVL_BLAB,("ProcessResources"));
    ASSERT(ResourceList);
    if (!ResourceList)
    {
        return STATUS_DEVICE_CONFIGURATION_ERROR;
    }

    //
    // Get counts for the types of resources.
    //
    ULONG   countIO     = ResourceList->NumberOfPorts();
    ULONG   countIRQ    = ResourceList->NumberOfInterrupts();
    ULONG   countDMA    = ResourceList->NumberOfDmas();
    ULONG   lengthIO    = ResourceList->FindTranslatedPort(0)->u.Port.Length;

#if (DBG)
    _DbgPrintF(DEBUGLVL_VERBOSE,("Starting MPU401 Port 0x%X",
        ResourceList->FindTranslatedPort(0)->u.Port.Start.LowPart) );
#endif

    NTSTATUS ntStatus = STATUS_SUCCESS;

    //
    // Make sure we have the expected number of resources.
    //
    if  (   (countIO != 1)
        ||  (countIRQ  > 1)
        ||  (countDMA != 0)
        ||  (lengthIO == 0)
        )
    {
        _DbgPrintF(DEBUGLVL_TERSE,("Unknown ResourceList configuraton"));
        ntStatus = STATUS_DEVICE_CONFIGURATION_ERROR;
    }

    if (NT_SUCCESS(ntStatus))
    {
        //
        // Get the port address.
        //
        m_pPortBase =
            PUCHAR(ResourceList->FindTranslatedPort(0)->u.Port.Start.QuadPart);

        ntStatus = InitializeHardware(m_pInterruptSync,m_pPortBase);
    }

    return ntStatus;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::NonDelegatingQueryInterface()
 *****************************************************************************
 * Obtains an interface.  This function works just like a COM QueryInterface
 * call and is used if the object is not being aggregated.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiUart::
NonDelegatingQueryInterface
(
    _In_           REFIID  Interface,
    _COM_Outptr_   PVOID * Object
)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB,("Miniport::NonDelegatingQueryInterface"));
    ASSERT(Object);

    if (IsEqualGUIDAligned(Interface,IID_IUnknown))
    {
        *Object = PVOID(PUNKNOWN(PMINIPORTMIDI(this)));
    }
    else
    if (IsEqualGUIDAligned(Interface,IID_IMiniport))
    {
        *Object = PVOID(PMINIPORT(this));
    }
    else
    if (IsEqualGUIDAligned(Interface,IID_IMiniportMidi))
    {
        *Object = PVOID(PMINIPORTMIDI(this));
    }
    else
    if (IsEqualGUIDAligned(Interface,IID_IMusicTechnology))
    {
        *Object = PVOID(PMUSICTECHNOLOGY(this));
    }
    else
    if (IsEqualGUIDAligned(Interface,IID_IPowerNotify))
    {
        *Object = PVOID(PPOWERNOTIFY(this));
    }
    else
    {
        *Object = NULL;
    }

    if (*Object)
    {
        //
        // We reference the interface for the caller.
        //
        PUNKNOWN(*Object)->AddRef();
        return STATUS_SUCCESS;
    }

    return STATUS_INVALID_PARAMETER;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::~CMiniportMidiUart()
 *****************************************************************************
 * Destructor.
 */
CMiniportMidiUart::~CMiniportMidiUart(void)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB,("~CMiniportMidiUart"));

    ASSERT(0 == m_NumCaptureStreams);
    ASSERT(0 == m_NumRenderStreams);
    
    //  reset the HW so we don't get any more interrupts
    if (m_UseIRQ && m_pInterruptSync)
    {
        (void) m_pInterruptSync->CallSynchronizedRoutine(InitLegacyMPU,PVOID(m_pPortBase));
    }
    else
    {
        (void) InitLegacyMPU(NULL,PVOID(m_pPortBase));
    }

    if (m_pInterruptSync)
    {
        m_pInterruptSync->Release();
        m_pInterruptSync = NULL;
    }
    if (m_pServiceGroup)
    {
        m_pServiceGroup->Release();
        m_pServiceGroup = NULL;
    }
    if (m_pPort)
    {
        m_pPort->Release();
        m_pPort = NULL;
    }
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::Init()
 *****************************************************************************
 * Initializes a the miniport.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiUart::
Init
(
    IN	    PUNKNOWN	    UnknownInterruptSync    OPTIONAL,
    IN      PRESOURCELIST   ResourceList,
    IN      PPORTMIDI       Port_,
    OUT     PSERVICEGROUP * ServiceGroup
)
{
    PAGED_CODE();

    ASSERT(ResourceList);
    if (!ResourceList)
    {
        return STATUS_DEVICE_CONFIGURATION_ERROR;
    }
    ASSERT(Port_);
    ASSERT(ServiceGroup);

    _DbgPrintF(DEBUGLVL_BLAB,("Init"));

    *ServiceGroup = NULL;
    m_pPortBase = 0;
    m_fMPUInitialized = FALSE;
 
    // This will remain unspecified if the miniport does not get any power 
    // messages.
    //
    m_PowerState.DeviceState = PowerDeviceUnspecified;
    
    //
    // AddRef() is required because we are keeping this pointer.
    //
    m_pPort = Port_;
    m_pPort->AddRef();

    // Set dataformat.
    //
    if (IsEqualGUIDAligned(m_MusicFormatTechnology, GUID_NULL))
    {
        RtlCopyMemory(  &m_MusicFormatTechnology, 
                        &KSMUSIC_TECHNOLOGY_PORT, 
                        sizeof(GUID));
    }
    RtlCopyMemory(  &PinDataRangesStream[0].Technology,
                    &m_MusicFormatTechnology,
                    sizeof(GUID));

    for (ULONG bufferCount = 0;bufferCount < kMPUInputBufferSize;bufferCount++)
    {
        m_MPUInputBuffer[bufferCount] = 0;
    }
    m_MPUInputBufferHead = 0;
    m_MPUInputBufferTail = 0;
    m_KSStateInput = KSSTATE_STOP;

    NTSTATUS ntStatus = STATUS_SUCCESS;

    m_NumRenderStreams = 0;
    m_NumCaptureStreams = 0;
    _DbgPrintF(DEBUGLVL_VERBOSE,("Init: resetting m_NumRenderStreams and m_NumCaptureStreams"));

    m_UseIRQ = TRUE;
    if (ResourceList->NumberOfInterrupts() == 0)
    {
        m_UseIRQ = FALSE;
    }

    ntStatus = PcNewServiceGroup(&m_pServiceGroup,NULL);
    if (NT_SUCCESS(ntStatus) && !m_pServiceGroup)   //  keep any error
    {
        ntStatus = STATUS_INSUFFICIENT_RESOURCES;
    }

    if (NT_SUCCESS(ntStatus))
    {
        *ServiceGroup = m_pServiceGroup;
        m_pServiceGroup->AddRef();

        //
        // Register the service group with the port early so the port is
        // prepared to handle interrupts.
        //
        m_pPort->RegisterServiceGroup(m_pServiceGroup);
    }

    if (NT_SUCCESS(ntStatus) && m_UseIRQ)
    {
/*
        //
        //  Due to a bug in the InterruptSync design, we shouldn't share
        //  the interrupt sync object.  Whoever goes away first 
        //  will disconnect it, and the other points off into nowhere.
        //  
        //  Instead we generate our own interrupt sync object.
        //
        UnknownInterruptSync = NULL;
*/
        if (UnknownInterruptSync)
        {
            ntStatus = 
                UnknownInterruptSync->QueryInterface
                (
                    IID_IInterruptSync,
                    (PVOID *) &m_pInterruptSync
                );

            if (!m_pInterruptSync && NT_SUCCESS(ntStatus))  //  keep any error
            {
                ntStatus = STATUS_INSUFFICIENT_RESOURCES;
            }
            if (NT_SUCCESS(ntStatus))
            {                                                                           //  run this ISR first
                ntStatus = m_pInterruptSync->
                    RegisterServiceRoutine(MPUInterruptServiceRoutine,PVOID(this),TRUE);
            }
        }
        else
        {   // create our own interruptsync mechanism.
            ntStatus = 
                PcNewInterruptSync
                (
                    &m_pInterruptSync,
                    NULL,
                    ResourceList,
                    0,                          // Resource Index
                    InterruptSyncModeNormal     // Run ISRs once until we get SUCCESS
                );

            if (!m_pInterruptSync && NT_SUCCESS(ntStatus))  //  keep any error
            {
                ntStatus = STATUS_INSUFFICIENT_RESOURCES;
            }
            if (NT_SUCCESS(ntStatus))
            {
                ntStatus = m_pInterruptSync->RegisterServiceRoutine(
                    MPUInterruptServiceRoutine,
                    PVOID(this),
                    TRUE);                //  run this ISR first
            }
            if (NT_SUCCESS(ntStatus))
            {
                ntStatus = m_pInterruptSync->Connect();
            }
        }
    }

    if (NT_SUCCESS(ntStatus))
    {
        ntStatus = ProcessResources(ResourceList);
    }

    if (!NT_SUCCESS(ntStatus))
    {
        //
        // clean up our mess
        //

        // clean up the interrupt sync
        if( m_pInterruptSync )
        {
            m_pInterruptSync->Release();
            m_pInterruptSync = NULL;
        }

        // clean up the service group
        if( m_pServiceGroup )
        {
            m_pServiceGroup->Release();
            m_pServiceGroup = NULL;
        }

        // clean up the out param service group.
        if (*ServiceGroup)
        {
            (*ServiceGroup)->Release();
            (*ServiceGroup) = NULL;
        }

        // release the port
        m_pPort->Release();
        m_pPort = NULL;
    }

    return ntStatus;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::NewStream()
 *****************************************************************************
 * Gets the topology.
 */
STDMETHODIMP_(NTSTATUS) 
CMiniportMidiUart::
NewStream
(
    OUT     PMINIPORTMIDISTREAM *   Stream,
    IN      PUNKNOWN                OuterUnknown    OPTIONAL,
    _When_((PoolType&NonPagedPoolMustSucceed)!=0,
        __drv_reportError("Must succeed pool allocations are forbidden. "
                          "Allocation failures cause a system crash"))
    IN      POOL_TYPE               PoolType,
    IN      ULONG                   PinID,
    IN      BOOLEAN                 Capture,
    IN      PKSDATAFORMAT           DataFormat,
    OUT     PSERVICEGROUP *         ServiceGroup
)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB, ("NewStream"));
    NTSTATUS ntStatus = STATUS_SUCCESS;

    // if we don't have any streams already open, get the hardware ready.
    if ((!m_NumCaptureStreams) && (!m_NumRenderStreams))
    {
        _DbgPrintF(DEBUGLVL_VERBOSE,("NewStream: m_NumRenderStreams and m_NumCaptureStreams are both 0, so ResetMPUHardware"));

        ntStatus = ResetMPUHardware(m_pPortBase);
        if (!NT_SUCCESS(ntStatus))
        {
            _DbgPrintF(DEBUGLVL_TERSE, ("CMiniportMidiUart::NewStream ResetHardware failed"));
            return ntStatus;
        }
    }
    else
    {
        _DbgPrintF(DEBUGLVL_VERBOSE,("NewStream: m_NumRenderStreams %d, m_NumCaptureStreams %d, no ResetMPUHardware",
                                     m_NumRenderStreams,m_NumCaptureStreams));
    }

    if  (   (   (m_NumCaptureStreams < kMaxNumCaptureStreams)
            &&  (Capture)  )
        ||  (   (m_NumRenderStreams < kMaxNumRenderStreams) 
            &&  (!Capture) )
        )
    {
        CMiniportMidiStreamUart *pStream =
            new(PoolType) CMiniportMidiStreamUart(OuterUnknown);

        if (pStream)
        {
            pStream->AddRef();

            ntStatus = 
                pStream->Init(this,m_pPortBase,Capture);

            if (NT_SUCCESS(ntStatus))
            {
                *Stream = PMINIPORTMIDISTREAM(pStream);
                (*Stream)->AddRef();

                if (Capture)
                {
                    m_NumCaptureStreams++;
                    *ServiceGroup = m_pServiceGroup;
                    (*ServiceGroup)->AddRef();
                }
                else
                {
                    m_NumRenderStreams++;
                    *ServiceGroup = NULL;
                }
                _DbgPrintF(DEBUGLVL_VERBOSE,("NewStream: succeeded, m_NumRenderStreams %d, m_NumCaptureStreams %d",
                                              m_NumRenderStreams,m_NumCaptureStreams));
            }

            pStream->Release();
        }
        else
        {
            ntStatus = STATUS_INSUFFICIENT_RESOURCES;
        }
    }
    else
    {
        ntStatus = STATUS_INVALID_DEVICE_REQUEST;
        if (Capture)
        {
            _DbgPrintF(DEBUGLVL_TERSE,("NewStream failed, too many capture streams"));
        }
        else
        {
            _DbgPrintF(DEBUGLVL_TERSE,("NewStream failed, too many render streams"));
        }
    }

    return ntStatus;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiUart::SetTechnology()
 *****************************************************************************
 * Sets pindatarange technology.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiUart::
SetTechnology
(
    __in    const GUID *            Technology
)
{
    PAGED_CODE();
    
    NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
    
    // Fail if miniport has already been initialized. 
    //
    if (NULL == m_pPort)
    {
        RtlCopyMemory(&m_MusicFormatTechnology, Technology, sizeof(GUID));
        ntStatus = STATUS_SUCCESS;
    }

    return ntStatus;
} // SetTechnology

/*****************************************************************************
 * CMiniportMidiUart::PowerChangeNotify()
 *****************************************************************************
 * Handle power state change for the miniport.
 */
#pragma code_seg("PAGE")
STDMETHODIMP_(void)
CMiniportMidiUart::
PowerChangeNotify
(
    __in    POWER_STATE             PowerState
)
{
    PAGED_CODE();
    
    _DbgPrintF(DEBUGLVL_VERBOSE, ("CMiniportMidiUart::PoweChangeNotify D%d", PowerState.DeviceState));
    
    switch (PowerState.DeviceState)
    {
        case PowerDeviceD0:
            if (m_PowerState.DeviceState != PowerDeviceD0) 
            {
                if (!NT_SUCCESS(InitializeHardware(m_pInterruptSync,m_pPortBase)))
                {
                    _DbgPrintF(DEBUGLVL_TERSE, ("InitializeHardware failed when resuming"));
                }
            }
            break;

        case PowerDeviceD1:
        case PowerDeviceD2:
        case PowerDeviceD3:
        default:
            break;
    }
    m_PowerState.DeviceState = PowerState.DeviceState;
} // PowerChangeNotify

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiStreamUart::NonDelegatingQueryInterface()
 *****************************************************************************
 * Obtains an interface.  This function works just like a COM QueryInterface
 * call and is used if the object is not being aggregated.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiStreamUart::
NonDelegatingQueryInterface
(
    _In_           REFIID  Interface,
    _COM_Outptr_   PVOID * Object
)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB,("Stream::NonDelegatingQueryInterface"));
    ASSERT(Object);

    if (IsEqualGUIDAligned(Interface,IID_IUnknown))
    {
        *Object = PVOID(PUNKNOWN(this));
    }
    else
    if (IsEqualGUIDAligned(Interface,IID_IMiniportMidiStream))
    {
        *Object = PVOID(PMINIPORTMIDISTREAM(this));
    }
    else
    {
        *Object = NULL;
    }

    if (*Object)
    {
        //
        // We reference the interface for the caller.
        //
        PUNKNOWN(*Object)->AddRef();
        return STATUS_SUCCESS;
    }

    return STATUS_INVALID_PARAMETER;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiStreamUart::SetFormat()
 *****************************************************************************
 * Sets the format.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiStreamUart::
SetFormat
(
    IN      PKSDATAFORMAT   Format
)
{
    PAGED_CODE();

    ASSERT(Format);

    _DbgPrintF(DEBUGLVL_VERBOSE,("CMiniportMidiStreamUart::SetFormat"));

    return STATUS_SUCCESS;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiStreamUart::~CMiniportMidiStreamUart()
 *****************************************************************************
 * Destructs a stream.
 */
CMiniportMidiStreamUart::~CMiniportMidiStreamUart(void)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_BLAB,("~CMiniportMidiStreamUart"));

    if (m_pMiniport)
    {
        if (m_fCapture)
        {
            m_pMiniport->m_NumCaptureStreams--;
        }
        else
        {
            m_pMiniport->m_NumRenderStreams--;
        }
        _DbgPrintF(DEBUGLVL_VERBOSE,("~CMiniportMidiStreamUart: m_NumRenderStreams %d, m_NumCaptureStreams %d",
                                      m_pMiniport->m_NumRenderStreams,m_pMiniport->m_NumCaptureStreams));

        m_pMiniport->Release();
    }
    else
    {
        _DbgPrintF(DEBUGLVL_VERBOSE,("~CMiniportMidiStreamUart, no miniport!!!: m_NumRenderStreams %d, m_NumCaptureStreams %d",
                                      m_pMiniport->m_NumRenderStreams,m_pMiniport->m_NumCaptureStreams));
    }
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiStreamUart::Init()
 *****************************************************************************
 * Initializes a stream.
 */
STDMETHODIMP_(NTSTATUS) 
CMiniportMidiStreamUart::
Init
(
    IN      CMiniportMidiUart * pMiniport,
    IN      PUCHAR              pPortBase,
    IN      BOOLEAN             fCapture
)
{
    PAGED_CODE();

    ASSERT(pMiniport);
    ASSERT(pPortBase);

    _DbgPrintF(DEBUGLVL_VERBOSE,("Init"));

    m_NumFailedMPUTries = 0;
    m_pMiniport = pMiniport;
    m_pMiniport->AddRef();

    m_pPortBase = pPortBase;
    m_fCapture = fCapture;

    return STATUS_SUCCESS;
}

#pragma code_seg("PAGE")
/*****************************************************************************
 * CMiniportMidiStreamUart::SetState()
 *****************************************************************************
 * Sets the state of the channel.
 */
STDMETHODIMP_(NTSTATUS)
CMiniportMidiStreamUart::
SetState
(
    IN      KSSTATE     NewState
)
{
    PAGED_CODE();

    _DbgPrintF(DEBUGLVL_VERBOSE,("SetState %d",NewState));

    if (NewState == KSSTATE_RUN)
    {
        if (!m_pMiniport->m_fMPUInitialized)
        {
            _DbgPrintF(DEBUGLVL_TERSE, ("CMiniportMidiStreamUart::SetState KSSTATE_RUN failed due to uninitialized MPU"));
            return STATUS_INVALID_DEVICE_STATE;
        }
    }

    if (m_fCapture)
    {
        m_pMiniport->m_KSStateInput = NewState;
        if (NewState == KSSTATE_STOP)   // STOPping
        {
            m_pMiniport->m_MPUInputBufferHead = 0;   // Previously read bytes are discarded.
            m_pMiniport->m_MPUInputBufferTail = 0;   // The entire FIFO is available.
        }
    }
    return STATUS_SUCCESS;
}

#pragma code_seg()
/*****************************************************************************
 * CMiniportMidiUart::Service()
 *****************************************************************************
 * DPC-mode service call from the port.
 */
STDMETHODIMP_(void) 
CMiniportMidiUart::
Service
(   void
)
{
    _DbgPrintF(DEBUGLVL_BLAB, ("Service"));
    _DbgPrintF(DEBUGLVL_VERBOSE,("Service: m_NumRenderStreams %d, m_NumCaptureStreams %d",
                                  m_NumRenderStreams,m_NumCaptureStreams));
    if (!m_NumCaptureStreams)
    {
        //  we should never get here....
        //  if we do, we must have read some trash,
        //  so just reset the input FIFO
        m_MPUInputBufferTail = m_MPUInputBufferHead = 0;
    }
}

#pragma code_seg()//**********************************************************************
// File: MemPressureReport.hpp
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Purpose:
// Interfaces or data structures for the test of Support DWM On.
//
// History:
// 09/04/2007 Created by Jimmy Chen.
//**********************************************************************
#ifndef __SUPPORT_DWM_ON__
#define __SUPPORT_DWM_ON__

#include <windows.h>

#define THREAD_SLEEP_TIME           50
#define DWM_COMPOSITION_OFF_TIME    4000

// Self define error codes
#define E_TESTSKIPPED           MAKE_DDHRESULT(0xffffff0)


#define D3DFVF_CUSTOMVERTEX             (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define MAX_TEXTURES_CREATED            1000

typedef struct
{
    float x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
} SIMPLE_VERTEX;

// AppDescriptor: store information about an application used for the test
typedef struct tagAppDescriptor
{
    struct    {
    	USHORT    ushAction;                     // Action_None will be used as "Terminator"
        DWORD     dwParameter;                   // parameter for the action   
        void      *pData;                        // pointer to test data 
    } AppOperations[2];                          // Operations for the application. 
} AppDescriptor, *PAppDescriptor;

// TestCaseDescriptor: store test cases specific information
typedef struct tagTestCaseDescriptor
{
	LPCTSTR         TestCaseName;       // The name of test case 
	BOOL            bEnabled;           // TRUE - the test case is enabled, otherwise disabled 
	USHORT          ExpectedResults[2]; // Expected test results. Verify_Result_None will be used as "Terminator" 
} TestCaseDescriptor, *PTestCaseDescriptor;

#endif // __SUPPORT_DWM_ON__
#include "Test_Include.fx"

int Test_Count = 146;

string TestInfo
<
	string TestType = "PS";
>
= "ps_2_0_inst_dp4";

PS_CRITERIA PS_001_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_001_Desc = "ps_2_0 : dp4 source reg combination t0, r0 is allowed";
string PS_001 = 
	"ps_2_0 "
	"dcl t0 "
	"mov r0, c0 "
	"dp4 r0, t0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_002_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_002_Desc = "ps_2_0 : dp4 source reg combination t0, c0 is allowed";
string PS_002 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_003_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_003_Desc = "ps_2_0 : dp4 source reg combination v0, r0 is allowed";
string PS_003 = 
	"ps_2_0 "
	"dcl v0 "
	"mov r0, c0 "
	"dp4 r0, v0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_004_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_004_Desc = "ps_2_0 : dp4 source reg combination v0, c0 is allowed";
string PS_004 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl v0 "
	"dp4 r0, v0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_005_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_005_Desc = "ps_2_0 : dp4 source reg combination r0, t0 is allowed";
string PS_005 = 
	"ps_2_0 "
	"dcl t0 "
	"mov r0, c0 "
	"dp4 r0, r0, t0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_006_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_006_Desc = "ps_2_0 : dp4 source reg combination r0, v0 is allowed";
string PS_006 = 
	"ps_2_0 "
	"dcl v0 "
	"mov r0, c0 "
	"dp4 r0, r0, v0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_007_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_007_Desc = "ps_2_0 : dp4 source reg combination r0, r1 is allowed";
string PS_007 = 
	"ps_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"dp4 r0, r0, r1 "
	"mov oC0, c0 ";

PS_CRITERIA PS_008_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_008_Desc = "ps_2_0 : dp4 source reg combination r0, c0 is allowed";
string PS_008 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"dp4 r0, r0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_009_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_009_Desc = "ps_2_0 : dp4 source reg combination c0, t0 is allowed";
string PS_009 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, c0, t0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_010_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_010_Desc = "ps_2_0 : dp4 source reg combination c0, v0 is allowed";
string PS_010 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl v0 "
	"dp4 r0, c0, v0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_011_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_011_Desc = "ps_2_0 : dp4 source reg combination c0, r0 is allowed";
string PS_011 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"dp4 r0, c0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_012_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_012_Desc = "ps_2_0 : dp4 source reg combination -t0, -c0 is allowed";
string PS_012 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, -t0, -c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_013_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_013_Desc = "ps_2_0 : dp4 source reg combination -t0, c0 is allowed";
string PS_013 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, -t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_014_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_014_Desc = "ps_2_0 : dp4 source reg combination t0, -c0 is allowed";
string PS_014 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0, -c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_015_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_015_Desc = "ps_2_0 : dp4 source reg combination t0, c0 is allowed";
string PS_015 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_016_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_016_Desc = "ps_2_0 : dp4 source reg combination t0.r, c0 is allowed";
string PS_016 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0.r, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_017_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_017_Desc = "ps_2_0 : dp4 source reg combination t0.g, c0 is allowed";
string PS_017 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0.g, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_018_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_018_Desc = "ps_2_0 : dp4 source reg combination t0.b, c0 is allowed";
string PS_018 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0.b, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_019_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_019_Desc = "ps_2_0 : dp4 source reg combination t0.a, c0 is allowed";
string PS_019 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0.a, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_020_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_020_Desc = "ps_2_0 : dp4 source reg combination t0.gbra, c0 is allowed";
string PS_020 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"dp4 r0, t0.gbra, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_021_Cri