#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef PathH
#define PathH
// --------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"
// --------------------------------------------------------------------------
namespace Bicycle
{
// --------------------------------------------------------------------------
namespace Path
{
// --------------------------------------------------------------------------
  tstring toNativeSeparators(const tstring& path); // "/" -> "\\"
  tstring replaceReservedChars(const tstring& path, tchar ch =TEXT('_'));

  void appendSeparator(tstring& dir);
  tstring join(const tstring& dir, const tstring& rel);
  tstring join(const tstring& dir, const tstring& rel1, const tstring& rel2);
  bool isDot(const tstring& dir); // "." or ".."

  tstring fileName(const tstring& path);   //  D:\\1\\2.3\\4.txt -> 4.txt
  tstring baseName(const tstring& path);   //  D:\\1\\2.3\\4.txt -> 4
  tstring extension(const tstring& path);  //  D:\\1\\2.3\\4.txt -> .txt
  tstring parent(const tstring& path);     //  D:\\1\\2.3\\4.txt -> D:\\1\\2.3

  enum EntryFlags
  {
    Files = 1,
    Dirs  = 2,
    Dots = 4,
    Recursive= 8,

    Entries = Dirs|Files,

    AllFiles=  Files|Recursive,
    AllDirs=   Dirs|Recursive,
    AllEntries= Files|Dirs|Recursive
  };

  // Search files and dirs
  size_t entry(Strings& entries,
               const tstring& dir,
               const tstring& mask= tstring(TEXT("*")),
               EntryFlags flags= Entries,
               const tstring& subDir= tstring());

  bool exists(const tstring& path); // is valid path
  bool isDir(const tstring& path);
  bool isRelative(const tstring& path);
  bool isSystemFolder(const tstring& path);
  bool isRoot(const tstring &path);

  tstring currentDir();
  void setCurrentDir(const tstring& dir);

  ulong fileSize(const tstring& path);

  tstring relativeTo(const tstring& from,const tstring& to);


	bool createDir(const tstring& path);
	bool removeDir(const tstring& path);

  bool copyFile(const tstring& path,const tstring& newPath,bool failIfExists=false);
  bool moveFile(const tstring& path,const tstring& newPath);
  bool renameFile(const tstring& path,const tstring& newPath);

  bool deleteFile(const tstring& path);

  // removeDir()
  // makeDir()
  // copyDir()

  // appPath()

  // bool hasPrefix(const tstring& path)
  // void appendPrefix(tstring& path)
  // bool quoted() / wrapped()
  // void normolize(tstring& path)  // add prefix and quote

} // Path
// --------------------------------------------------------------------------
} // Bicycle
// --------------------------------------------------------------------------
#endif // PathH
