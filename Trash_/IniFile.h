#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include <cctype>
//----------------------------------------------------------------------
class IniFile
{
public:
  typedef char CharT;
  typedef std::basic_string<CharT>  String;
  typedef std::vector<String> StringVector;

  typedef std::basic_istream<CharT> IStream;
  typedef std::basic_ostream<CharT> OStream;
  typedef std::basic_ifstream<CharT> IFStream;
  typedef std::basic_ofstream<CharT> OFStream;

  typedef String::iterator SIterator;

  typedef std::size_t Index;
  typedef std::size_t SizeType;


  String str(Index row,Index index,Index length)
  {
    return lines_[row].substr(index,length);
  }

  void change(Index row,Index index, Index& length,const String& str)
  {
    lines_[row].erase(index,length);
    lines_[row].insert(index,str);
		length= str.length();
  }

  struct ValueInfo
  {
    Index row;
    Index    index;
    SizeType length;
  };

  struct SectionInfo
  {
    Index row;
    Index rowCount;

    std::map<String,ValueInfo> keyValues;
  };

public:
  IniFile();

  String value(const String& section, const String& key,const String& defaultValue="");
  void setValue(const String& section, const String& key,const String& value);

  bool exists(const String& section);
  bool exists(const String& section, const String& key);

  void remove(const String& section);
  void remove(const String& section,const String& key);

  IStream& load(IStream& stream);
  OStream& save(OStream& stream);

  bool load(const char* fileName);
  bool save(const char* fileName);

private:
  void parse();
  // void reIndexete();

private:
  StringVector lines_;
  typedef std::map<String,SectionInfo> Sections;
  Sections sections_;
};
//----------------------------------------------------------------------
IniFile::IniFile()
{
}
//----------------------------------------------------------------------
IniFile::IStream& IniFile::load(IniFile::IStream& stream)
{
  lines_.clear();
  String line;
  while(!stream.eof() && std::getline(stream,line))
    lines_.push_back(line);

  parse();
  return stream;
}
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
IniFile::Index ingnoreSpaces(const IniFile::String& line, IniFile::Index start)
{
  for(IniFile::Index i=start; i<line.size(); ++i)
    if(!std::isspace(line[i]))
      return i;
  return IniFile::String::npos;
}
//----------------------------------------------------------------------
bool readSectionName(const IniFile::String& line, IniFile::Index start, IniFile::String& sectionName)
{
  sectionName.clear();
  for(IniFile::Index i=start; i<line.size(); ++i)
    if(line[i]== ']')
    {
      sectionName= line.substr(start,i-start);
      break;
    }
  return !sectionName.empty();
}
//----------------------------------------------------------------------
bool readKeyValue(const IniFile::String& line,
                  IniFile::Index start,
                  IniFile::String& key,
									IniFile::Index& valueIndex,
									IniFile::SizeType& valueLength)
{
  key.clear();
 
  IniFile::Index i= start;
  for(; i<line.size(); ++i)
    if(line[i] == '=')
    {
      key= line.substr(start,i-start);
      break;
    }

  if(key.empty())
    return  false;

  start= ++i;
  IniFile::Index lastNotSpace= i;
  for(; i<line.size(); ++i)
  {
    if(line[i]!= ';')
    {
      if(!std::isspace(line[i]))
        lastNotSpace= i;
    }
    else
      break;
  }

	valueIndex= start;
	valueLength= lastNotSpace+1-start; 
  return true;
}
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void IniFile::parse()
{
  sections_.clear();
	String currentSectionName;

	Sections::iterator section_it= sections_.end();

  for(SizeType r=0; r<lines_.size(); ++r)
  {
    Index start= ingnoreSpaces(lines_[r],0);
    if(start==String::npos)
      continue;

    switch(lines_[r][start])
    {
			case ';' :	continue;
			
			case '[' :
			{
        String sectionName;
				if(!readSectionName(lines_[r],start+1,sectionName))
					continue;

				SectionInfo info;
				info.row= r;
				info.rowCount= 1;
				section_it= 
					sections_.insert(std::make_pair(sectionName,info)).first;
      } break;

			default:
			{
				if(section_it==sections_.end())
						continue;

				String key;
				ValueInfo info;
				if(!readKeyValue(lines_[r],start,key,info.index,info.length))
						continue;

				info.row= r;
				SectionInfo& si= section_it->second;
				si.keyValues.insert(std::make_pair(key,info));
				si.rowCount= r-si.row+1;
			} break;
    }
  }
}
//----------------------------------------------------------------------
IniFile::OStream& IniFile::save(IniFile::OStream& stream)
{
  std::copy(lines_.begin(),lines_.end(),
            std::ostream_iterator<String>(stream,"\n")) ;
  return stream;
}
//----------------------------------------------------------------------
bool IniFile::load(const char* fileName)
{
  IFStream ifs(fileName);
  if(!ifs)
    return false;

  if(load(ifs))
    return true;
  return false;
}
//----------------------------------------------------------------------
bool IniFile::save(const char* fileName)
{
  OFStream ofs(fileName);
  if(!ofs)
    return false;

  if(save(ofs))
    return true;
  return false;
}
//----------------------------------------------------------------------
IniFile::String IniFile::value( const IniFile::String& section,
                                const IniFile::String& key,
                                const IniFile::String& defaultValue)
{
	std::map<String,SectionInfo>::const_iterator 
			s_it= sections_.find(section);

	if(s_it==sections_.end())
			return "error 1";

  const SectionInfo& si= s_it->second;

	std::map<String,ValueInfo>::const_iterator 
			kv_it= si.keyValues.find(key);

	if(kv_it== si.keyValues.end())
			return "error 2";

	const ValueInfo& vi= kv_it->second; 
	return str(vi.row,vi.index,vi.length);
}
//----------------------------------------------------------------------
void IniFile::setValue( const IniFile::String& section,
                        const IniFile::String& key,
                        const IniFile::String& value)
{
	std::map<String,SectionInfo>::iterator 
			s_it= sections_.find(section);

	if(s_it==sections_.end())
	{
		lines_.push_back("["+section+"]");	 
		SectionInfo si;
		si.row= lines_.size()-1;
		si.rowCount= 1;
		s_it= sections_.insert(std::make_pair(section,si)).first;
	}

  SectionInfo& si= s_it->second;

	std::map<String,ValueInfo>::iterator 
			kv_it= si.keyValues.find(key);

	if(kv_it==si.keyValues.end())
	{
		lines_.insert(lines_.begin()+si.row+si.rowCount,key+"="+value);
		++si.rowCount;

		ValueInfo vi;
		vi.row=     si.row+si.rowCount+1;
		vi.index=   key.length()+1;
		vi.length=  value.length();

		kv_it= si.keyValues.insert(std::make_pair(key,vi)).first;
		// reidex (si.row+si.rowCount)
	}
	else
	{
  	ValueInfo& vi= kv_it->second; 
  	change(vi.row,vi.index,vi.length,value);
	}
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
bool IniFile::exists(const IniFile::String& section)
{
  return sections_.find(section)!= sections_.end();
}
//----------------------------------------------------------------------
bool IniFile::exists(const IniFile::String& section,
                     const IniFile::String& key)
{
  return false;
}
//----------------------------------------------------------------------
void IniFile::remove(const IniFile::String& section)
{

}
//----------------------------------------------------------------------
void IniFile::remove(const IniFile::String& section,
                     const IniFile::String& key)
{

}
//----------------------------------------------------------------------