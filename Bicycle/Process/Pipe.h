#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef PipeH
#define PipeH
//---------------------------------------------------------------------------
#include "Global.h"
#include "SystemException.h"
#include "Buffer.h"
#include "NonCopyable.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
	struct ProcessError  // enum class
	{
		enum:ulong
		{
				Success= ERROR_SUCCESS,
				WaitTimeOut= WAIT_TIMEOUT,      // #258 (0x102) The wait operation timed out.

				Broken=  ERROR_BROKEN_PIPE, // [Error #109 Канал был закрыт.]  The pipe has been ended.
				NoData=  ERROR_NO_DATA,     // [Error #232 Идет закрытие канала.] The pipe is being closed.
				Incomplete= ERROR_IO_INCOMPLETE // 996  Overlapped I/O event is not in a signaled state.
		};
	};
//---------------------------------------------------------------------------
//   Server  &  Client Pipes
//---------------------------------------------------------------------------
class ServerPipe: private NonCopyable
{
	public:
		ServerPipe(const tstring& name= tstring());
		virtual ~ServerPipe();

		void create();
		void connect();

		HANDLE handle()const;
		bool isValide()const;
		void disconnect(ulong& errorCode);
		void close();

		tstring name()const;
		void setName(const tstring& name);

		void setOpenMode(ulong mode);
		void setPipeMode(ulong mode);
		void setBufferSize(ulong size);

	protected:
		OVERLAPPED& overlapped();// used in friends PipeReader & PipeWriter
		friend class PipeReader;
		friend class PipeWriter;

	private:
		tstring name_;
		ulong openMode_;
		ulong pipeMode_;
		ulong maxInstances_;
		ulong	bufferSize_;
		ulong defaultTimeOut_;

		HANDLE handle_;
		OVERLAPPED overlapped_;
};
//---------------------------------------------------------------------------
class ClientPipe: private NonCopyable
{
	public:
		ClientPipe(const tstring& name= tstring());
		virtual ~ClientPipe();

		void open();

		HANDLE handle()const;
		bool isValide()const;
		void close();

		tstring name()const;
		void setName(const tstring& name);

		void setDesiredAccess(ulong access);
		void setSharedMode(ulong mode);
		void setFlagsAndAttributes(ulong flagsAndAttr);

	private:
		tstring name_;
		ulong desiredAccess_;
		ulong sharedMode_;
		ulong flagsAndAttributes_;

		HANDLE handle_;
};
//---------------------------------------------------------------------------
//    PipeReader  &  PipeWriter
//---------------------------------------------------------------------------
class PipeReader: private NonCopyable
{
	public:
		PipeReader(ServerPipe* pipe= NULL);
		virtual ~PipeReader();

		void setPipe(ServerPipe* pipe);
		void setTimeOut(ulong msecs);
    ulong read(char* data, ulong size, ulong& errorCode);

	private:
		ServerPipe* pipe_;
		ulong  timeOut_;
};
//---------------------------------------------------------------------------
class PipeWriter: private NonCopyable
{
	public:
		PipeWriter(ServerPipe* pipe= NULL);
		virtual ~PipeWriter();

		void setPipe(ServerPipe* pipe);
		void setTimeOut(ulong msecs);

    ulong write(const char* data, ulong size, ulong& errorCode);
	private:
		ServerPipe* pipe_;
		ulong timeOut_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif