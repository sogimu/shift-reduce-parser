#pragma once

#include "i_syntax_node.h"

#include <functional>
#include <memory>
#include <vector>
#include <type_traits>
#include <concepts>

template< typename T >
concept DerivedFromInterface = std::derived_from< T, ISyntaxNode >;

template< DerivedFromInterface... Nodes, typename Container >
bool IsLastNodesIs(
   const Container& container,
   const std::function< ISyntaxNodeSP( const typename Container::value_type& ) >& delegate = []( const typename Container::value_type& value ) { return value; } )
{
   if( sizeof...( Nodes ) > container.size() )
      return false;

   return std::apply(
      [ & ]( auto&&... args )
      {
         size_t index = container.size() - sizeof...( args );
         return ( ( dynamic_cast< std::decay_t< decltype( args ) >* >( delegate( container[ index++ ] ).get() ) ) && ... );
      },
      std::tuple< Nodes... >() );
}

template< DerivedFromInterface Node >
bool IsNode( const ISyntaxNodeSP& node )
{
   return static_cast< bool >( std::dynamic_pointer_cast< Node >( node ) );
}

template< DerivedFromInterface... Nodes, typename Container >
std::tuple< std::shared_ptr< Nodes >... > DowncastLastNodesTo(
   const Container& container,
   const std::function< ISyntaxNodeSP( const typename Container::value_type& ) >& delegate = []( const typename Container::value_type& value ) { return value; } )
{
   if( sizeof...( Nodes ) > container.size() )
      throw std::runtime_error( "Not enough nodes in container!" );

   return std::apply(
      [ & ]( auto&&... args )
      {
         size_t index = container.size() - sizeof...( args ) + 1;
         auto it = container.begin();
         std::advance( it, index );
         return std::make_tuple( std::dynamic_pointer_cast< std::decay_t< decltype( args ) > >( delegate( *it-- ) )... );
      },
      std::tuple< Nodes... >() // Create an empty tuple of Nodes types
   );
}
