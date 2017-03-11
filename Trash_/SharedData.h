//---------------------------------------------------------------------------
#ifndef SharedDataH
#define SharedDataH
//---------------------------------------------------------------------------
#include <windows.h>
#include <string>
#include <map>
#include <stdexcept>

#include "MutexLocker.h"
//---------------------------------------------------------------------------
struct Value
{
	double bid;
	double ask;
};
//---------------------------------------------------------------------------
typedef TCHAR tchar;
typedef std::basic_string<tchar>tstring;
//---------------------------------------------------------------------------
class SharedData
{
private:  // not copyable
	SharedData(const SharedData&);
	SharedData& operator= (const SharedData&);

public:
	SharedData(const tstring& name);
	virtual ~SharedData();

	void create();
	void open();
	void close();

	void   setValue(int id, double bid, double ask);
	double getBid(int id) const;
	double getAsk(int id) const;
	void   registrateId(int id);

protected:
	void mapView();
	void initView();

private:
	tstring name_;
	HANDLE mutex_;
	HANDLE fileMap_;
	PVOID view_;
	const int timeOut_;
	mutable std::map<int,int> values_;
	typedef std::map<int,int>::iterator iterator;
	int current;
};
//---------------------------------------------------------------------------
#endif
