#include <iostream>
#include "Experimental/Volume.h"

using namespace std;
namespace Bi= Bicycle;

int main()
{
  try
  {
    Bi::Volume volume;
    cout<<"volume: "<< volume.value() << endl;
    volume.setValue(1.00); // 100%
    cout<<"volume: "<< volume.value() << endl;
  }
  catch(const std::exception& e)
  {
    cerr<< e.what() << endl;
  }

  getchar();
  return 0;
}

