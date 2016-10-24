#include "Path.h"

#include <algorithm>
#include <iterator>
#include <cassert>

#include <Shlwapi.h>

using namespace Bicycle;
// ----------------------------------------------------
const tstring reservedCharset= TEXT("<>:\"/\\|?*");
const tstring pathSeparators= TEXT("\\/");
// ----------------------------------------------------
tstring Path::toNativeSeparators(const tstring &path)
{
  tstring result;
  std::replace_copy(path.begin(),path.end(),
                    std::back_inserter(result),
                    TEXT('/'),
                    TEXT('\\'));
  return result;
}
// ----------------------------------------------------
bool isReserved(tchar ch)
{
  return reservedCharset.find(ch)!= tstring::npos;
}
// ----------------------------------------------------
bool isSeparator(tchar ch)
{
  return pathSeparators.find(ch)!= tstring::npos;
}
// ----------------------------------------------------
tstring Path::replaceReservedChars(const tstring &path, tchar ch/*= "_" */)
{
  tstring result;
  std::replace_copy_if(path.begin(),path.end(),
                    std::back_inserter(result),
                    isReserved,
                    ch);
  return result;
}
// ----------------------------------------------------
void Path::appendSeparator(tstring& dir)
{
  if(dir.empty() && !isSeparator(dir[dir.size()-1]))
    dir.append(TEXT("\\"));
}
// ----------------------------------------------------
tstring Path::join(const tstring& dir, const tstring& rel)
{
  if(!dir.empty() && !isSeparator(dir[dir.size()-1]))
    return dir+TEXT("\\")+rel;
  return dir+rel;
}
// ----------------------------------------------------
tstring Path::join(const tstring& dir, const tstring& rel1, const tstring& rel2)
{
  return join(join(dir,rel1),rel2);
}
// ----------------------------------------------------
bool Path::isDot(const tstring& dir)
{
  return dir== TEXT(".") || dir==TEXT("..");
}
//-----------------------------------------------------
tstring Path::fileName(const tstring& path)
{
  std::size_t s= path.find_last_of(pathSeparators);
  if(s==tstring::npos)
    return path;

  return path.substr(s+1,path.size()-(s+1));
}
// ----------------------------------------------------
tstring Path::baseName(const tstring &path)
{
  std::size_t p= path.find_last_of(pathSeparators+TEXT('.'));
  if(p==tstring::npos)
    return path;

  if(path[p]==TEXT('.'))
  {
    std::size_t s= path.find_last_of(pathSeparators);
    if(s==tstring::npos)
      s= 0;
    else s++;
    return path.substr(s,p-s);
  }
  else
    return path.substr(p+1,path.size()-(p+1));

  return tstring();
}
// ----------------------------------------------------
tstring Path::extension(const tstring& path)
{
  std::size_t p= path.find_last_of(pathSeparators+TEXT('.'));
  if(p!=tstring::npos && path[p]==TEXT('.'))
    return path.substr(p,path.size()-(p));

  return tstring();
}
// ----------------------------------------------------
tstring Path::parent(const tstring &path)
{
  std::size_t s= path.find_last_of(pathSeparators);
  if(s==tstring::npos)
    return tstring();

  return path.substr(0,s);
}
//==================================================================
size_t Path::entry(Strings& entries,
                   const tstring &dir,
                   const tstring& mask,
                   EntryFlags flags,
                   const tstring& subDir)
{
  // Seach by mask
  WIN32_FIND_DATA data;
  HANDLE handle = FindFirstFile(join(dir,subDir,mask).c_str(), &data);
  if(handle!=INVALID_HANDLE_VALUE)
  {
    do
    {
      if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // is Dir
      {
        if((flags & Dirs) && (!isDot(data.cFileName) || (flags & Dots)))
           entries.push_back(join(subDir,data.cFileName));
      }
      else if(flags & Files) // is File or some else
        entries.push_back(join(subDir,data.cFileName));
    }
    while(FindNextFile(handle,&data)!=0);
    FindClose(handle);
  }
  // Recursive search in sub dirs
  if(flags & Recursive)
  {
    Strings subDirs;
    entry(subDirs, join(dir,subDir), TEXT("*"), Dirs);
    for(std::size_t i=0; i<subDirs.size(); ++i)
       entry(entries,dir,mask,flags,join(subDir,subDirs[i]));
  }
  return entries.size();
}
// ----------------------------------------------------
bool Path::exists(const tstring &path)
{
  return PathFileExists(path.c_str()) == TRUE;
}
// ----------------------------------------------------
bool Path::isDir(const tstring &path)
{
  return (GetFileAttributes(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

// ----------------------------------------------------
bool Path::isRelative(const tstring &path)
{
  return PathIsRelative(path.c_str())== TRUE;
}
// ----------------------------------------------------
bool Path::isSystemFolder(const tstring &path)
{
  return PathIsSystemFolder(path.c_str(),0)== TRUE;
}
// ----------------------------------------------------
bool Path::isRoot(const tstring &path)
{
  return PathIsRoot(path.c_str())== TRUE;
}
// ----------------------------------------------------
tstring Path::currentDir()
{
  ulong length= GetCurrentDirectory(0,NULL);
  if(!length)
    throw SystemException("Path: ");

  tstring dir(length,TEXT('\0'));
  if(!GetCurrentDirectory(dir.size(),&dir[0]))
    throw SystemException("Path: ");

  return dir;
}
// ----------------------------------------------------
void Path::setCurrentDir(const tstring &dir)
{
  if(!SetCurrentDirectory(dir.c_str()))
    throw SystemException("Path: ");
}
// ----------------------------------------------------
ulong Path::fileSize(const tstring &path)
{
   WIN32_FILE_ATTRIBUTE_DATA data;

   if (!GetFileAttributesEx(path.c_str(), GetFileExInfoStandard, (void*)&data))
     throw SystemException("Path: ");

   assert(0 == data.nFileSizeHigh);
   return data.nFileSizeLow;
}
// ----------------------------------------------------
tstring Path::relativeTo(const tstring &from, const tstring &to)
{
  tstring out(MAX_PATH,TEXT('\0'));
  if(!PathRelativePathTo(&out[0],
                     from.c_str(),
                     FILE_ATTRIBUTE_DIRECTORY,
                     to.c_str(),
                     FILE_ATTRIBUTE_NORMAL))
    throw SystemException("Path: ");
  out.resize(out.find(TEXT('\0')));
  return out;
}
// ----------------------------------------------------







