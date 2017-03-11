#include <iostream>
#include <string>
#include <vector>

#include "Algorithm/Trim.h"
#include "Algorithm/IsAnyOf.h"
#include "Algorithm/Split.h"

#include "Algorithm/Join.h"
#include "Algorithm/Filter.h"
#include "Algorithm/Wrap.h"
#include "Algorithm/SearchEx.h"
#include "Algorithm/SplitEx.h"
#include "Algorithm/EndsWith.h"
#include "Algorithm/StartsWith.h"

using namespace std;
using namespace Bicycle;

int main()
{
  string text= "  +*abc+*  ";

  // Trim
  cout<<"\""<< text<<"\"" << endl;
  cout<<"Trim  right copy: \""<< trim_right_copy(text)<<"\""<< endl;
  cout<<"Trim left copy: \"" << trim_left_copy(text) <<"\""<< endl;
  cout<<"Trim copy: \""<< trim_copy(text)      <<"\""<< endl;

  trim(text);
  cout<<"Trim: \""<< text << endl;

  cout<<"Trim copy if *+: \""
      << trim_copy_if(text,is_any_of("*+"))
      <<"\""<<endl;
  cout<<endl;

  // Split
  text= ",1;2;;3,4,,5;";
  vector<string> items;

  cout<<"\""<< text << "\""<<endl;

  cout<<"Split by: \";,\""<<endl;

  items.clear();
  split(items,text,is_any_of(";,"));

  for(size_t i=0; i<items.size(); ++i)
    cout<<"\""<< items[i] <<"\""<<endl;
  cout<<endl;

  cout<<"Split skip empty parts and use C-string:"<<endl;

  items.clear();
  split(items,",1;2;;3,4,,5;",is_any_of(";,"),true);
  for(size_t i=0; i<items.size(); ++i)
    cout<<"\""<< items[i] <<"\""<<endl;
  cout<<endl;

  cout<<"Join with \"|\""<<endl;
  cout<<"\""<< join(items, "|") <<"\""<<endl;
  cout<<endl;

  cout<< "Filter digits:" <<endl;
  cout<<"\""<< filter(text,is_any_of("1234567890")) <<"\""<<endl;
  cout<<endl;


  cout<<"Split ex by \";;\" and \",,\":"<<endl;

  char splitters[2][3] = { ";;", ",," };

  items.clear();
  split_ex(items,text,splitters);

  for(size_t i=0; i<items.size(); ++i)
    cout<<"\""<< items[i] <<"\""<<endl;
  cout<<endl;

  text = "C:\\Program Files\\1.txt";
  cout<< "Wrap copy path quoted "<< text <<endl;
  cout<< wrap_copy(text,"\"")<<endl;

  text ="html";
  cout<<"Wrap tag \"html\""<<endl;
  wrap(text,"<",">");
  cout<< text <<endl;
  cout<< "is wrapped: "<<boolalpha<< is_wrapped(text,"<",">")<<endl;

  cout<<"Unwrap tag \"html\"" <<endl;
  cout<< unwrap_copy(text,"<",">")<<endl;
  unwrap(text,"<",">");
  cout<< text <<endl;
  cout<<endl;

  text= "FirstTextLast";
  cout<<"Starts with \"First\": "<< boolalpha << starts_with(text,"First") <<endl;
  cout<<"Ends with \"Last\": "    << boolalpha << ends_with(text,"Last")   <<endl;

  cout<<"Starts with case insensetive \"first\": "<< boolalpha
      << starts_with(text,"first",CaseInsensitiveCmp<char>()) <<endl;
  cout<<"Ends with case insensetive \"last\": "<< boolalpha
      << ends_with(text,"last",CaseInsensitiveCmp<char>()) <<endl;

  cout<< endl;

  std::vector<string> searched;
  searched.push_back("1");
  searched.push_back("20");
  searched.push_back("300");

  text= "abc1de2f20g300j";
  cout<< text << endl;
  cout<< "Search ex" << endl;

  typedef search_result<string::iterator,vector<string>::iterator > Result;

  Result result= search_ex(text.begin(),text.end(),searched.begin(),searched.end());
  while(result.last!=text.end())
  {
    cout<< *result.found <<endl; // in vector searched
    cout<< std::string(result.first,result.last) <<endl; // in string source
    result=
      search_ex(result.last,text.end(),searched.begin(),searched.end());
  }

  cout<< endl;
  text= "abc1de2f20g300j";
  cout<<"\""<< text << "\""<< endl;
  cout<< "apply to upper case:" << endl;

  cout<< apply(text,toupper)<< endl;

  string out;
  apply("abcdef",out,toupper);
  cout<< out << endl;

  getchar();
  return 0;
}

