// ---------------------------------------------------------------------------
#include "Buffer.h"
#include <assert.h>
// ---------------------------------------------------------------------------
using namespace Bicycle;
// ---------------------------------------------------------------------------
Buffer::Buffer(Buffer::SizeType size)
 :
	data_(size,'\0'),
	g_(0),
	p_(0)
{
}
// ---------------------------------------------------------------------------
Buffer::~Buffer()
{
}
// ---------------------------------------------------------------------------
void Buffer::clear()
{
	g_= 0;
	p_= 0;
}
// ---------------------------------------------------------------------------
void Buffer::resize(Buffer::SizeType size)
{
	data_.resize(size);
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::size()const
{
	return data_.size();
}
// ---------------------------------------------------------------------------
Buffer::Pointer Buffer::data()
{
	return &data_[0];
}
// ---------------------------------------------------------------------------
Buffer::Pointer Buffer::putPtr()
{
  return data()+p_;
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::availableSpace()
{
	return data_.size()-p_;
}
// ---------------------------------------------------------------------------
void Buffer::addToPutPos(Buffer::SizeType size)
{
	p_+= size;
	assert(p_<=data_.size());
}
// ---------------------------------------------------------------------------
template<class ForwardIt1, class ForwardIt2>
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
									 ForwardIt2 s_first, ForwardIt2 s_last)
{
	for(;;++first)
	{
		ForwardIt1 it= first;
		for(ForwardIt2 s_it= s_first; ; ++it, ++s_it)
		{
			if(s_it==s_last)
				return first;

			if(it==last)
				return first; // !!!   particle

			if(!(*it==*s_it))
				break;
		}
	}
}
// ---------------------------------------------------------------------------
Buffer::SearchResult
	Buffer::searchDelemiter(const std::string& delemiter,Buffer::PosType& c)
{
	Iterator gi= data_.begin()+g_;
	Iterator pi= data_.begin()+p_;

	Iterator ci= ::search(gi,pi,delemiter.begin(),delemiter.end());
	c= std::distance(data_.begin(),ci);

	if(ci==pi)
		 return NotFound;
	else
	{
	 if(p_-c<delemiter.size())
		 return Partical;
	 else
		 return Found;
	}
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::readLine(std::string& line,
									bool& success,
									const std::string& delemiter)
{
	assert(g_<=p_);

	PosType c= 0;
	SizeType length= 0;

	SearchResult sr= searchDelemiter(delemiter,c);

	line.append(data()+g_,c-g_);
	switch(sr)
	{
		case NotFound:
		{
			 length= p_-g_;
			 g_= p_= 0;
			 success= false;
		} break;

		case Partical:
		{
			 length= c-g_;
			 g_= c;
			 success= false;
		}  break;

		case Found:
		{
			 length= c+delemiter.size()-g_;
			 g_= c+delemiter.size();
			 success= true;
		}  break;
	}
	return length;
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::contentSize()const
{
	return p_-g_;
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::readData(Buffer::Pointer outData,
															Buffer::SizeType size,
															bool* success)
{
	const SizeType m= std::min(size, contentSize() );
	memcpy(outData,data()+g_,m);
	g_+= m;

	if(success)
		*success= (m==size);

	return m;
}
// ---------------------------------------------------------------------------
Buffer::SizeType Buffer::readString(std::string& outStr,
																		Buffer::SizeType size,
																		bool* success)
{
	const SizeType m= std::min(size, contentSize());
	outStr.append(data()+g_,m);
	g_+= m;

	if(success)
		*success= (m==size);

	return m;
}
// ---------------------------------------------------------------------------
