#pragma once

#include <iostream>
#include <map>
#include <ostream>
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

   void writeValueToLocalVarible( const std::string& name, int value )
   {
      mScope.back()[ name ] = value;
   }

   void print() const
   {
      std::cout << "*************" << std::endl;
      int index = mScope.size();
      for( auto it = mScope.rbegin(); it != mScope.rend(); ++it )
      {
         const auto& layer = *it;
         std::cout << "=LAYER (" << std::to_string( index ) << "): ";
         for( const auto& [ key, value ] : layer )
         {
            std::cout << key << " == " << std::to_string( value ) << ", ";
         }
         --index;
         std::cout << std::endl;
      }
      std::cout << "*************" << std::endl;
   }

private:
   mutable std::deque< std::map< std::string, int > > mScope;
};
