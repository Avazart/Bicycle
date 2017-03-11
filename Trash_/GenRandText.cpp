//---------------------------------------------------------------------------
#pragma hdrstop
#include "GenRandText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#include <vector>
#include <deque>
#include <boost/foreach.hpp>

#define reverse_foreach BOOST_REVERSE_FOREACH
#define foreach BOOST_FOREACH
//---------------------------------------------------------------------------
struct Place
{
	 int first,last;
	 std::vector<String> words;
};
//---------------------------------------------------------------------------
void __fastcall GenIndexes( int N,
														const   std::vector<Place>&   places,
														/*out*/ std::deque<int>& indexes)
{
	reverse_foreach(const Place& place, places)
	{
		indexes.push_front(N% place.words.size());
		N/= place.words.size();
	}
};
//---------------------------------------------------------------------------
int __fastcall Parse( const   String& AText,
											/*out*/ std::vector<Place>& places)
{
	String Word;
	bool start= false;
	srand(time(0));
	int maxN= 1;

	for(int i=1; i<=AText.Length(); ++i)
	{
		if(!start)
		{
			if(AText[i]==L'{')
			{
				places.push_back(Place());
				places.back().first= i;
				start= true;
				continue;
			}

			if(AText[i]==L'}')
				 return -1; // Нет открывающей скобки перед }

			if(AText[i]==L'|')
				 return -2; // Нет открывающей скобки перед |
		}
		else
		{
			if(AText[i]==L'}')
			{
				if(!places.empty())
				{
					 places.back().last= i;
					 places.back().words.push_back(Word);
					 maxN*= places.back().words.size();
				}
				Word="";
				start= false;
				continue;
			}

			if(AText[i]==L'|')
			{
				if(!places.empty())
					 places.back().words.push_back(Word);

				Word="";
				continue;
			};

			if(AText[i]==L'{')
				 return -3; // Вложенные скобки недопустимы.

			Word+= AText[i];
		}
	}

	return maxN;
}
//---------------------------------------------------------------------------
String __fastcall BuildText(String AText,
														const std::vector<Place>& places,
														const std::deque<int>& indexes)
{
	int i= indexes.size()-1;
	reverse_foreach(const Place& place, places)
	{
		AText.Delete(place.first,place.last-place.first+1);
		AText.Insert(place.words[indexes[i--]],place.first);
	}
	return AText;
}
//---------------------------------------------------------------------------
//void PrintWords(std::vector<Place>& places)
//{
//	foreach(const Place& place, places)
//	{
//		Form1->RichEdit2->Lines->Add(String (place.first)+" "+String(place.last));
//		foreach(const String& word, place.words)
//		{
//			Form1->RichEdit2->Lines->Add(word);
//		}
//	}
//}//---------------------------------------------------------------------------
String __fastcall My::GenRandText(int& N, const String& AText)
{
	std::vector<Place> places;
	int maxN= Parse(AText,places);

	if(maxN<0)
		return "Ошибочный синтаксис!";

	if(maxN<=N)
		N=0;

	std::deque<int> indexes;
	GenIndexes(N, places, indexes);

return BuildText(AText,places,indexes);
}
//---------------------------------------------------------------------------

