
// IDirect3D8 methods
SIG_MACRO(D3D8_AddRef,                          _OUT(_DATA))
SIG_MACRO(D3D8_Release,                         _OUT(_DATA))
SIG_MACRO(D3D8_GetAdapterCount,                 _OUT(_DATA))
SIG_MACRO(D3D8_GetAdapterDisplayMode,           _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(D3D8_GetAdapterIdentifier,            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(D3D8_GetAdapterModeCount,             _OUT(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_GetAdapterMonitor,               _OUT(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_GetDeviceCaps,                   _OUT(_DATA) _IN(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(D3D8_EnumAdapterModes,                _OUT(_DATA) _IN(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(D3D8_RegisterSoftwareDevice,          _OUT(_DATA) _IN(_DATA)) // REVIEW: If these tests are ported to a test platform supporting RegisterSoftwareDevice, the initialization function pointer needs to be translated
SIG_MACRO(D3D8_CheckDeviceFormat,               _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_CheckDeviceMultiSampleType,      _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_CheckDeviceType,                 _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_CheckDepthStencilMatch,          _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(D3D8_CreateDevice,                    _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA) _ADD(_ADDRESS))

// IDirect3DDevice8 methods
SIG_MACRO(DEV8_AddRef,                          _OUT(_DATA))
SIG_MACRO(DEV8_Release,                         _OUT(_DATA))
SIG_MACRO(DEV8_CreateAdditionalSwapChain,       _OUT(_DATA) _PIN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateCubeTexture,               _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateDepthStencilSurface,       _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateImageSurface,              _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateIndexBuffer,               _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateRenderTarget,              _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateTexture,                   _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateVertexBuffer,              _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_CreateVolumeTexture,             _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_ApplyStateBlock,                 _OUT(_DATA) _IN(_SBLOCK))
SIG_MACRO(DEV8_BeginStateBlock,                 _OUT(_DATA))
SIG_MACRO(DEV8_EndStateBlock,                   _OUT(_DATA) _ADD(_SBLOCK))
SIG_MACRO(DEV8_CreateStateBlock,                _OUT(_DATA) _IN(_DATA) _ADD(_SBLOCK))
SIG_MACRO(DEV8_DeleteStateBlock,                _OUT(_DATA) _DEL(_SBLOCK))
SIG_MACRO(DEV8_CaptureStateBlock,               _OUT(_DATA) _IN(_SBLOCK))
SIG_MACRO(DEV8_GetClipStatus,                   _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetClipStatus,                   _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_GetRenderState,                  _OUT(_DATA) _IN(_DATA) _OUT(_DATA))
SIG_MACRO(DEV8_SetRenderState,                  _OUT(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetRenderTarget,                 _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_SetRenderTarget,                 _OUT(_DATA) _IN(_ADDRESS) _IN(_ADDRESS))
SIG_MACRO(DEV8_GetTransform,                    _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetTransform,                    _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_MultiplyTransform,               _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_Clear,                           _OUT(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetViewport,                     _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetViewport,                     _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_GetClipPlane,                    _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetClipPlane,                    _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_GetLight,                        _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetLight,                        _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_LightEnable,                     _OUT(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetLightEnable,                  _OUT(_DATA) _IN(_DATA) _OUT(_DATA))
SIG_MACRO(DEV8_GetMaterial,                     _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetMaterial,                     _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_GetTexture,                      _OUT(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_SetTexture,                      _OUT(_DATA) _IN(_DATA) _IN(_ADDRESS))
SIG_MACRO(DEV8_GetTextureStageState,            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _OUT(_DATA))
SIG_MACRO(DEV8_SetTextureStageState,            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_UpdateTexture,                   _OUT(_DATA) _IN(_ADDRESS) _IN(_ADDRESS))
SIG_MACRO(DEV8_ValidateDevice,                  _OUT(_DATA) _OUT(_DATA))
SIG_MACRO(DEV8_GetCurrentTexturePalette,        _OUT(_DATA) _OUT(_DATA))
SIG_MACRO(DEV8_SetCurrentTexturePalette,        _OUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetPaletteEntries,               _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_SetPaletteEntries,               _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_CreateVertexShader,              _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _ADD(_VSHADER) _IN(_DATA))
SIG_MACRO(DEV8_DeleteVertexShader,              _OUT(_DATA) _DEL(_VSHADER))
SIG_MACRO(DEV8_GetVertexShader,                 _OUT(_DATA) _ADD(_VSHADER))
SIG_MACRO(DEV8_SetVertexShader,                 _OUT(_DATA) _IN(_VSHADER))
SIG_MACRO(DEV8_GetVertexShaderConstant,         _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_SetVertexShaderConstant,         _OUT(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetVertexShaderDeclaration,      _OUT(_DATA) _IN(_VSHADER) _POUT(_DATA) _BI(_DATA))
SIG_MACRO(DEV8_GetVertexShaderFunction,         _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _BI(_DATA))
SIG_MACRO(DEV8_CreatePixelShader,               _OUT(_DATA) _PIN(_DATA) _ADD(_PSHADER))
SIG_MACRO(DEV8_DeletePixelShader,               _OUT(_DATA) _DEL(_PSHADER))
SIG_MACRO(DEV8_GetPixelShader,                  _OUT(_DATA) _ADD(_PSHADER))
SIG_MACRO(DEV8_SetPixelShader,                  _OUT(_DATA) _IN(_PSHADER))
SIG_MACRO(DEV8_GetPixelShaderConstant,          _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_SetPixelShaderConstant,          _OUT(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetPixelShaderFunction,          _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _BI(_DATA))
SIG_MACRO(DEV8_Present,                         _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_Reset,                           _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_BeginScene,                      _OUT(_DATA))
SIG_MACRO(DEV8_EndScene,                        _OUT(_DATA))
SIG_MACRO(DEV8_DrawIndexedPrimitive,            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_DrawIndexedPrimitiveUP,          _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_DrawPrimitive,                   _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_DrawPrimitiveUP,                 _OUT(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_DeletePatch,                     _OUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_DrawRectPatch,                   _OUT(_DATA) _IN(_DATA) _BI(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_DrawTriPatch,                    _OUT(_DATA) _IN(_DATA) _BI(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_GetStreamSource,                 _OUT(_DATA) _IN(_DATA) _ADD(_ADDRESS) _OUT(_DATA))
SIG_MACRO(DEV8_SetStreamSource,                 _OUT(_DATA) _IN(_DATA) _IN(_ADDRESS) _IN(_DATA))
SIG_MACRO(DEV8_GetIndices,                      _OUT(_DATA) _ADD(_ADDRESS) _OUT(_DATA))
SIG_MACRO(DEV8_SetIndices,                      _OUT(_DATA) _IN(_ADDRESS) _IN(_DATA))
SIG_MACRO(DEV8_GetAvailableTextureMem,          _OUT(_DATA))
SIG_MACRO(DEV8_GetCreationParameters,           _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_GetDeviceCaps,                   _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_GetDirect3D,                     _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_GetInfo,                         _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_GetRasterStatus,                 _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_GetDisplayMode,                  _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(DEV8_GetBackBuffer,                   _OUT(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_GetDepthStencilSurface,          _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(DEV8_GetGammaRamp,                    _POUT(_DATA))
SIG_MACRO(DEV8_SetGammaRamp,                    _IN(_DATA) _PIN(_DATA))
SIG_MACRO(DEV8_CopyRects,                       _OUT(_DATA) _IN(_ADDRESS) _PIN(_DATA) _IN(_DATA) _IN(_ADDRESS) _PIN(_DATA))
SIG_MACRO(DEV8_GetFrontBuffer,                  _OUT(_DATA) _IN(_ADDRESS))
SIG_MACRO(DEV8_ProcessVertices,                 _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_DATA) _IN(_ADDRESS) _IN(_DATA))
SIG_MACRO(DEV8_ResourceManagerDiscardBytes,     _OUT(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_TestCooperativeLevel,            _OUT(_DATA))
SIG_MACRO(DEV8_SetCursorPosition,               _IN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(DEV8_SetCursorProperties,             _OUT(_DATA) _IN(_DATA) _IN(_DATA) _IN(_ADDRESS))
SIG_MACRO(DEV8_ShowCursor,                      _OUT(_DATA) _IN(_DATA))

// IDirect3DSurface8
SIG_MACRO(SUR8_AddRef,                          _OUT(_DATA))
SIG_MACRO(SUR8_Release,                         _OUT(_DATA))
SIG_MACRO(SUR8_GetContainer,                    _OUT(_DATA) _PIN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(SUR8_GetDevice,                       _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(SUR8_GetDesc,                         _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(SUR8_LockRect,                        _OUT(_DATA) _POUT(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(SUR8_UnlockRect,                      _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(SUR8_GetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _POUT(_DATA) _BI(_DATA)) 
SIG_MACRO(SUR8_SetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(SUR8_FreePrivateData,                 _OUT(_DATA) _PIN(_DATA))

// IDirect3DVolume8
SIG_MACRO(VOL8_AddRef,                          _OUT(_DATA))
SIG_MACRO(VOL8_Release,                         _OUT(_DATA))
SIG_MACRO(VOL8_GetContainer,                    _OUT(_DATA) _PIN(_DATA) _ADD(_ADDRESS))
SIG_MACRO(VOL8_GetDevice,                       _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(VOL8_GetDesc,                         _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(VOL8_LockBox,                         _OUT(_DATA) _POUT(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(VOL8_UnlockBox,                       _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(VOL8_GetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _POUT(_DATA) _BI(_DATA)) 
SIG_MACRO(VOL8_SetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(VOL8_FreePrivateData,                 _OUT(_DATA) _PIN(_DATA))

// IDirect3DResource8
SIG_MACRO(RES8_AddRef,                          _OUT(_DATA))
SIG_MACRO(RES8_Release,                         _OUT(_DATA))
SIG_MACRO(RES8_GetType,                         _OUT(_DATA))
SIG_MACRO(RES8_GetDevice,                       _OUT(_DATA) _ADD(_ADDRESS))
SIG_MACRO(RES8_GetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _POUT(_DATA) _BI(_DATA)) 
SIG_MACRO(RES8_SetPrivateData,                  _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _IN(_DATA))
SIG_MACRO(RES8_FreePrivateData,                 _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(RES8_GetPriority,                     _OUT(_DATA))
SIG_MACRO(RES8_SetPriority,                     _OUT(_DATA) _IN(_DATA))
SIG_MACRO(RES8_PreLoad,                         _VOID)

// IDirect3DBaseTexture8
SIG_MACRO(BTX8_GetLevelCount,                   _OUT(_DATA))
SIG_MACRO(BTX8_GetLOD,                          _OUT(_DATA))
SIG_MACRO(BTX8_SetLOD,                          _OUT(_DATA) _IN(_DATA))

// IDirect3DTexture8
SIG_MACRO(TEX8_GetLevelDesc,                    _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(TEX8_LockRect,                        _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(TEX8_UnlockRect,                      _OUT(_DATA) _IN(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(TEX8_AddDirtyRect,                    _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(TEX8_GetSurfaceLevel,                 _OUT(_DATA) _IN(_DATA) _ADD(_ADDRESS))

// IDirect3DCubeTexture8
SIG_MACRO(CTX8_GetLevelDesc,                    _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(CTX8_LockRect,                        _OUT(_DATA) _IN(_DATA) _IN(_DATA) _POUT(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(CTX8_UnlockRect,                      _OUT(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(CTX8_AddDirtyRect,                    _OUT(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(CTX8_GetCubeMapSurface,               _OUT(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))

// IDirect3DVolumeTexture8
SIG_MACRO(VTX8_GetLevelDesc,                    _OUT(_DATA) _IN(_DATA) _POUT(_DATA))
SIG_MACRO(VTX8_LockBox,                         _OUT(_DATA) _IN(_DATA) _POUT(_DATA) _PIN(_DATA) _IN(_DATA))
SIG_MACRO(VTX8_UnlockBox,                       _OUT(_DATA) _IN(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(VTX8_AddDirtyBox,                     _OUT(_DATA) _PIN(_DATA))
SIG_MACRO(VTX8_GetVolumeLevel,                  _OUT(_DATA) _IN(_DATA) _ADD(_ADDRESS))

// IDirect3DVertexBuffer8
SIG_MACRO(VRB8_GetDesc,                         _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(VRB8_Lock,                            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _OUT(_DATA) _IN(_DATA))
SIG_MACRO(VRB8_Unlock,                          _OUT(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA))

// IDirect3DIndexBuffer8
SIG_MACRO(IXB8_GetDesc,                         _OUT(_DATA) _POUT(_DATA))
SIG_MACRO(IXB8_Lock,                            _OUT(_DATA) _IN(_DATA) _IN(_DATA) _OUT(_DATA) _IN(_DATA))
SIG_MACRO(IXB8_Unlock,                          _OUT(_DATA) _IN(_DATA) _IN(_DATA) _PIN(_DATA))

// IDirect3DSwapChain8
SIG_MACRO(SWC8_AddRef,                          _OUT(_DATA))
SIG_MACRO(SWC8_Release,                         _OUT(_DATA))
SIG_MACRO(SWC8_Present,                         _OUT(_DATA) _PIN(_DATA) _PIN(_DATA) _IN(_DATA) _PIN(_DATA))
SIG_MACRO(SWC8_GetBackBuffer,                   _OUT(_DATA) _IN(_DATA) _IN(_DATA) _ADD(_ADDRESS))

#undef SIG_MACRO
