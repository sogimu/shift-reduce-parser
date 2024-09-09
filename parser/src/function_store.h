#pragma once

#include "nonterminals/function_syntax_node.h"
#include <cstddef>
#include <string>
#include <cstdio>
#include <utility>

using namespace std;

class FunctionStore
{
public:
   void pushScope()
   {
      mScope.emplace_back( std::map< std::pair< std::string, size_t >, FunctionSyntaxNodeSP >{} );
   }

   void popScope()
   {
      mScope.pop_back();
   }

   FunctionSyntaxNodeSP operator[]( const std::pair< std::string, size_t >& function_key )
   {
      auto it = std::find_if( mScope.rbegin(), mScope.rend(),
                              [ &function_key ]( const auto& layer ) -> bool
                              {
                                 const auto& it = layer.find( function_key );
                                 return ( it != layer.end() );
                              } );
      if( it != mScope.rend() )
      {
         return ( *it )[ function_key ];
      }
      return mScope.back()[ function_key ];
   }

   FunctionSyntaxNodeSP operator[]( const std::pair< std::string, size_t >& function_key ) const
   {
      auto it = std::find_if( mScope.rbegin(), mScope.rend(),
                              [ &function_key ]( const auto& layer ) -> bool
                              {
                                 const auto& it = layer.find( function_key );
                                 return ( it != layer.end() );
                              } );
      if( it != mScope.rend() )
      {
         return ( *it )[ function_key ];
      }
      return mScope.back()[ function_key ];
   }

   void insert( const std::pair< std::string, size_t >& function_key, const FunctionSyntaxNodeSP& node )
   {
      mScope.back().insert( { function_key, node } );
   }

private:
   mutable std::deque< std::map< std::pair< std::string, size_t >, FunctionSyntaxNodeSP > > mScope;
};
