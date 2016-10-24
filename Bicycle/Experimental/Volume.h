#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef VolumeH
#define VolumeH
//----------------------------------------------------------
#include "../Global.h"
#include "../NonCopyable.h"
//---------------------------------------------------------------------------
#include <windows.h>
#include <commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
// --------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class Volume: private NonCopyable
{
public:
  Volume();
  ~Volume();

  bool mute();
  void setMute(bool mute);

  float value();
  void  setValue(float value);

  void  increaseValue(float value);
  void  decreaseValue(float value);

private:
  void checkError(HRESULT hr);
  void close();

  GUID guid_;
  IMMDeviceEnumerator *enumerator_;
  IMMDevice *device_;
  IAudioEndpointVolume *endPointVolume_;
};
//---------------------------------------------------------------------------
//      VolumeCallback
//---------------------------------------------------------------------------
class VolumeCallback : public IAudioEndpointVolumeCallback
{
public:
  VolumeCallback();
  ~VolumeCallback();

  ULONG STDMETHODCALLTYPE AddRef();
  ULONG STDMETHODCALLTYPE Release();

  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID** ppvInterface);
  HRESULT STDMETHODCALLTYPE OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify);

private:
  LONG cRef_;
  double value_;
};
//---------------------------------------------------------------------------
} // Bicycle
//---------------------------------------------------------------------------
#endif
