#pragma once

#include <string>

using namespace std;

class VaribleStore
{
public:
   void pushScope()
   {
      mScope.emplace_back( std::map< std::string, int >{} );
   }

   void popScope()
   {
      mScope.pop_back();
   }

   int& operator[]( const std::string& name )
   {
      auto it = std::find_if( mScope.rbegin(), mScope.rend(),
                              [ &name ]( const auto& layer ) -> bool
                              {
                                 const auto& it = layer.find( name );
                                 return ( it != layer.end() );
                              } );
      if( it != mScope.rend() )
      {
         return ( *it )[ name ];
      }
      return mScope.back()[ name ];
   }

   const int& operator[]( const std::string& name ) const
   {
      auto it = std::find_if( mScope.rbegin(), mScope.rend(),
                              [ &name ]( const auto& layer ) -> bool
                              {
                                 const auto& it = layer.find( name );
                                 return ( it != layer.end() );
                              } );
      if( it != mScope.rend() )
      {
         return ( *it )[ name ];
      }
      return mScope.back()[ name ];
   }

private:
   mutable std::deque< std::map< std::string, int > > mScope;
};
