//---------------------------------------------------------------------------
#include "Volume.h"
// ---------------------------------------------------------------------------
using namespace Bicycle;
// ---------------------------------------------------------------------------
#define SAFE_RELEASE(punk)  \
  if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }
//---------------------------------------------------------------------------
Volume::Volume()
  : //guid_(GUID_NULL),
    enumerator_(0),
    device_(0),
    endPointVolume_(0)
{
  CoInitialize(NULL);

  HRESULT hr = CoCreateGuid(&guid_);
  checkError(hr);

  hr=
      CoCreateInstance( __uuidof(MMDeviceEnumerator),
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        __uuidof(IMMDeviceEnumerator),
                        (void**)&enumerator_);
  checkError(hr);

  hr= enumerator_->GetDefaultAudioEndpoint(eRender, eConsole, &device_);
  checkError(hr);

  hr= device_->Activate( __uuidof(IAudioEndpointVolume),
                         CLSCTX_ALL,
                         NULL,
                         (void**)&endPointVolume_);
  checkError(hr);

  //	hr= endPointVolume_->RegisterControlChangeNotify((IAudioEndpointVolumeCallback*)&callback_);
  //	checkError(hr);

  InitCommonControls();
}
//---------------------------------------------------------------------------
void Volume::close()
{
  if(enumerator_)
  {
    //endPointVolume_->UnregisterControlChangeNotify((IAudioEndpointVolumeCallback*)&callback_);
  }

  SAFE_RELEASE(enumerator_)
      SAFE_RELEASE(device_)
      SAFE_RELEASE(endPointVolume_)
      CoUninitialize();
}
//---------------------------------------------------------------------------
void Volume::checkError(HRESULT hr)
{
  if(FAILED(hr))
  {
    close();
    throw std::runtime_error("Ошибка при работе со звуком!");
  }
}
//---------------------------------------------------------------------------
Volume::~Volume()
{
  close();
}
// ---------------------------------------------------------------------------
bool Volume::mute()
{
  BOOL mute_= 0;
  HRESULT hr= endPointVolume_->GetMute(&mute_);
  checkError(hr);
  return mute_==TRUE;
}
//---------------------------------------------------------------------------
void Volume::setMute(bool mute_)
{
  HRESULT hr= endPointVolume_->SetMute(mute_, &guid_);
  checkError(hr);
}
// ---------------------------------------------------------------------------
float Volume::value()
{
  float value= 0;
  HRESULT hr= endPointVolume_->GetMasterVolumeLevelScalar(&value);
  checkError(hr);
  return value;
}
//---------------------------------------------------------------------------
void Volume::setValue(float value)
{
  if(value>1)      value= 1;
  else if(value<0) value= 0;

  HRESULT hr=
      endPointVolume_->SetMasterVolumeLevelScalar(value,&guid_);
  checkError(hr);
}
//---------------------------------------------------------------------------
void Volume::increaseValue(float value)
{
  setValue(this->value()+value);
}
// ---------------------------------------------------------------------------
void Volume::decreaseValue(float value_)
{
  setValue(value()-value_);
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//                     VolumeCallback
// ---------------------------------------------------------------------------
VolumeCallback::VolumeCallback() : cRef_(1)
{
}
// ---------------------------------------------------------------------------
VolumeCallback::~VolumeCallback()
{
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE VolumeCallback::AddRef()
{
  return InterlockedIncrement(& cRef_);
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE VolumeCallback::Release()
{
  ULONG ulRef= InterlockedDecrement(&cRef_);
  if(0==ulRef)
  {
    delete this;
  }
  return ulRef;
}
// ---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE
VolumeCallback::QueryInterface(REFIID riid, VOID** ppvInterface)
{
  if (IID_IUnknown== riid)
  {
    AddRef();
    *ppvInterface= (IUnknown*)this;
  }
  else if (__uuidof(IAudioEndpointVolumeCallback)== riid)
  {
    AddRef();
    *ppvInterface= (IAudioEndpointVolumeCallback*)this;
  }
  else
  {
    *ppvInterface= NULL;
    return E_NOINTERFACE;
  }
  return S_OK;
}
//---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE
VolumeCallback::OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify)
{
  if (pNotify== NULL)
  {
    return E_INVALIDARG;
  }

  value_= pNotify->fMasterVolume; //pNotify->bMuted;
  return S_OK;
};
//--------------------------------------------------------------------------
