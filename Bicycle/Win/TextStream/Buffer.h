#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef BufferH
#define BufferH
//---------------------------------------------------------------------------
#include "Win/Common/Global.h"
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class Buffer
{
	private:
		typedef char ValueType;
		typedef std::vector<ValueType> Container;
		typedef	Container::iterator Iterator;
		typedef	Container::const_iterator CIterator;

	public:
		typedef ValueType* Pointer;
		typedef const Pointer CPointer;
		typedef Container::size_type SizeType;
		typedef SizeType PosType;

		Buffer(SizeType size= DEFAULT_BUFF_SIZE);
		virtual ~Buffer();

		void resize(SizeType size);
		SizeType size()const;

		void clear();

		SizeType readLine(std::string& line, bool& success,
											const std::string& delemiter= CRLF);

		SizeType readData(Pointer outData, size_t size, bool* success=0);
		SizeType readString(std::string& outStr,size_t size, bool* success=0);

		Pointer  putPtr();
		SizeType availableSpace();
		void addToPutPos(SizeType size);

	private:
		Pointer  data();
		SizeType contentSize() const;

		enum SearchResult { Found, Partical, NotFound };
		SearchResult searchDelemiter(const std::string& delemiter,PosType& pos);

	private:
		Container data_;

		PosType g_;   // index pos to get data
		PosType p_;   // index pos to put data
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
