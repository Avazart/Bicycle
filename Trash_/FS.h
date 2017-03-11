

bool pathExists(const tstring& path)
{
 // PathFileExists
}


// PathRelativePathTo
// PathRemoveExtension
// PathIsDirectory
// PathIsFileSpec

class Dir
{
   public:
    Dir(const tstring& path=TEXT("."));
   
	void exists()const; 
    Dir root()const;

    tstring name()const;
	void setName(const tstring& name); 
	
	Strings files();
	Strings dirs();
};

class File
{
    public:
	  File(const tstring& path=tstring());
	  
      Dir dir()const;
      tstring fileName()const; 	  
	  tstring baseName()const;
	  tstring ext()const;
	  
	  void rename(const tstring& newName);
	  void move(const Dir& dir);
};