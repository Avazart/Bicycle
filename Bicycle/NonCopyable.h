#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef NonCopyableH
#define NonCopyableH
//---------------------------------------------------------------------------
namespace Bicycle
{
  class NonCopyable
  {
    protected:
      NonCopyable() {}
      ~NonCopyable() {}
    private:
      NonCopyable( const NonCopyable& );
      const NonCopyable& operator=( const NonCopyable& );
  };
}
//---------------------------------------------------------------------------
#endif
