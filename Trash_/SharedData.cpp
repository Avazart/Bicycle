//---------------------------------------------------------------------------
#pragma hdrstop
#include "SharedData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
SharedData::SharedData(const tstring& name) :
	 name_(name),
	 mutex_(NULL),
	 fileMap_(NULL),
	 view_(NULL),
	 timeOut_(1000),
	 current(0)
{
};
//---------------------------------------------------------------------------
/* virtual */ SharedData::~SharedData()
{
	close();
};
//---------------------------------------------------------------------------
void SharedData::close()
{
	if (mutex_) {	CloseHandle(mutex_);	 mutex_= NULL;	}
	if(fileMap_){	CloseHandle(fileMap_); fileMap_= NULL;}
	if (view_)	{	UnmapViewOfFile(view_);view_= NULL;  	}
	current= 0;
}
//---------------------------------------------------------------------------
void SharedData::create()
{
	if (!mutex_ && !fileMap_)
	{
		const size_t memSize_= values_.size()*sizeof(Value);
		mutex_ = CreateMutex(NULL, true,(name_+TEXT("_MUTEX")).c_str());
		if(!mutex_)
			throw std::runtime_error("Error!Can not create mutex.");

		fileMap_= CreateFileMapping( INVALID_HANDLE_VALUE,
														 NULL,
														 PAGE_READWRITE,
														 0,
														 memSize_,
														 (name_+TEXT("_FILE_MAPPING")).c_str() );
		if (!fileMap_)
			throw std::runtime_error("Error!Can not create mapping.");

		mapView();   //
		initView();
		ReleaseMutex(mutex_);
	}
}
//---------------------------------------------------------------------------
void SharedData::open()
{
	if (!mutex_ && !fileMap_)
	{
		mutex_ = OpenMutex(SYNCHRONIZE,false,(name_+TEXT("_MUTEX")).c_str());
		if(!mutex_)
			throw std::runtime_error("Error! Can not open mutex.");

		fileMap_= OpenFileMapping(FILE_MAP_READ| FILE_MAP_WRITE, FALSE, (name_+TEXT("_FILE_MAPPING")).c_str());
		if (!fileMap_)
			throw std::runtime_error("Error! Can not create mapping.");

		mapView();
	}
}
//---------------------------------------------------------------------------
/*protected*/ void SharedData::mapView()
{
	view_= MapViewOfFile(fileMap_, FILE_MAP_READ| FILE_MAP_WRITE, 0, 0, 0);
	if (!view_)
		throw std::runtime_error("Error!Can not create mapping view.");

	//const size_t memSize_= 1024;
	//memset(view_, -1, memSize_);
}
//---------------------------------------------------------------------------
/*protected*/ void SharedData::initView()
{
	if (!view_)
		throw std::runtime_error("Error! View not created");
}
//---------------------------------------------------------------------------
void SharedData::registrateId(int id)
{
	if(values_.find(id)==values_.end())
		values_[id]= current++;
}
//---------------------------------------------------------------------------
void SharedData::setValue(int id, double bid, double ask)
{
	if (!view_)
		throw std::runtime_error("Error! View not created.");

	iterator v= values_.find(id);
	if(v==values_.end())
		return;

	MutexLoker loker(mutex_,timeOut_);
	if(!loker.loked())
		return;

	Value* p= (Value*)view_+v->second;
	p->bid= bid;
	p->ask= ask;
};
//---------------------------------------------------------------------------
double SharedData::getBid(int id) const
{
	iterator v= values_.find(id);
	if(v==values_.end())
		return -1;

	MutexLoker loker(mutex_,timeOut_);
	if(!loker.loked())
		return -1;

	Value* p= (Value*)view_+v->second;
	return p->bid;
}
//---------------------------------------------------------------------------
double SharedData::getAsk(int id) const
{
	iterator v= values_.find(id);
	if(v==values_.end())
		return -1;

	MutexLoker loker(mutex_,timeOut_);
	if(!loker.loked())
		 return -1;

	Value* p= (Value*)view_+v->second;
	return p->ask;
}
//---------------------------------------------------------------------------
