#pragma once

#include "i_syntax_node.h"
#include "syntax_node_empty_visitor.h"

#include <functional>
#include <memory>
#include <optional>
#include <stack>
#include <stdexcept>
#include <vector>
#include <list>

template< typename Node, typename PreFunc, typename PostFunc >
void iterative_dfs( const Node& start, PreFunc pre_func, PostFunc post_func )
{
   std::stack< std::pair< Node, bool > > stack;
   stack.emplace( start, true );

   while( !stack.empty() )
   {
      auto& [ node, is_pre_order ] = stack.top();

      if( is_pre_order )
      {
         bool is_found = pre_func( node );
         is_pre_order = false;

         if( !is_found )
         {
            const auto& childern = node->Children();
            for( auto it = childern.rbegin(); it != childern.rend(); ++it )
            {
               const auto& child = *it;
               stack.emplace( child, true );
            }
         }
      }
      else
      {
         post_func( node );
         stack.pop();
      }
   }
}

template< typename Node, typename PreFunc >
void iterative_dfs( const Node& start, PreFunc pre_func )
{
   iterative_dfs( start, pre_func, []( const auto& ) {} );
}

template< typename Node >
class StackDFS
{
public:
   StackDFS( std::stack< std::pair< Node, bool > >& stack )
      : mStack{ stack }
   {
   }

   void push( const ISyntaxNodeSP& node )
   {
      mStack.emplace( node, true );
   }

   void push( const std::vector< ISyntaxNodeSP >& nodes )
   {
      for( auto it = nodes.rbegin(); it != nodes.rend(); ++it )
      {
         const auto& child = *it;
         push( child );
      }
   }

   void pushChildrenOf( const ISyntaxNodeSP& node )
   {
      const auto& childern_value = node->Children();
      push( childern_value );
   }

   void popUntil( const ISyntaxNodeSP& node )
   {
   }

private:
   std::stack< std::pair< Node, bool > >& mStack;
};

template< typename Node, typename PreFunc, typename PostFunc >
void iterative_managed_dfs( const Node& start, PreFunc pre_func, PostFunc post_func )
{
   std::stack< std::pair< Node, bool > > stack;

   StackDFS< Node > stack_dfs{ stack };
   stack.emplace( start, true );

   while( !stack.empty() )
   {
      auto& [ node, is_pre_order ] = stack.top();

      if( is_pre_order )
      {
         /* const auto& children_opt =  */ pre_func( node, stack_dfs );
         // stack.emplace( node, false );
         is_pre_order = false;

         // if( !children_opt )
         //    continue;
         // const auto& childern_value = children_opt.value();
         // for( auto it = childern_value.rbegin(); it != childern_value.rend();
         // ++it )
         // {
         //    const auto& child = *it;
         //    stack.emplace( child, true );
         // }
      }
      else
      {
         post_func( node );
         stack.pop();
      }
   }
}

template< typename Node, typename PreFunc >
void iterative_managed_dfs( const Node& start, PreFunc pre_func )
{
   iterative_managed_dfs( start, pre_func, []( const auto& ) {} );
}

template< typename Node, typename PreFunc, typename PostFunc, typename GetChildrenReverseIterators >
void iterative_dfs2( const Node& start, const PreFunc& pre_func, const PostFunc& post_func, const GetChildrenReverseIterators& get_children_reverse_iterators )
{
   std::stack< std::pair< Node, bool > > stack;
   stack.emplace( start, true );

   while( !stack.empty() )
   {
      auto& [ node, is_pre_order ] = stack.top();

      if( is_pre_order )
      {
         bool is_found = pre_func( node );
         is_pre_order = false;

         if( !is_found )
         {
            const auto& d = node;
            const auto& [ rbegin, rend ] = get_children_reverse_iterators( node );
            for( auto it = rbegin; it != rend; ++it )
            {
               const auto& c = *it;
               stack.emplace( c, true );
            }
         }
      }
      else
      {
         post_func( node );
         stack.pop();
      }
   }
}

template< typename Node, typename PreFunc, typename GetChildrenReverseIterators >
void iterative_dfs2( const Node& start, const PreFunc& pre_func, const GetChildrenReverseIterators& get_children_reverse_iterators )
{
   iterative_dfs2( start, pre_func, []( const auto& ) {}, get_children_reverse_iterators );
}
// helper type for the visitor #4
template< class... Ts >
struct overloaded : Ts...
{
   using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template< class... Ts >
overloaded( Ts... ) -> overloaded< Ts... >;

using Stack = std::deque< ISyntaxNodeSP >;
static Stack last_n_syntax_nodes( const Stack& stack, size_t n )
{
   if( stack.size() < n )
      return {};

   auto it = stack.begin();
   std::advance( it, stack.size() - n );

   return Stack{ it, stack.end() };
}

static void iterate_over_last_n_nodes( const Stack& stack, size_t n, const SyntaxNodeEmptyVisitor::Handlers& handlers )
{
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const auto& nodes = last_n_syntax_nodes( stack, n );
   for( const auto& node : nodes )
   {
      if( !node )
         throw std::runtime_error( "Node is not exist" );
      node->accept( visitor );
   }
}

template< typename Range >
class zip_container
{
   Range c1;
   Range c2;

public:
   zip_container( const Range& c1, const Range& c2 )
      : c1( c1 )
      , c2( c2 )
   {
   }

   class Iterator
   {
   public:
      using iterator_category = std::input_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = std::pair< std::optional< typename Range::Iterator::value_type >, std::optional< typename Range::Iterator::value_type > >;
      using reference = value_type&;
      using pointer = value_type*;

      Iterator( const auto& c1, const auto& c1end, const auto& c2, const auto& c2end )
         : mC1{ c1 }
         , mC1End{ c1end }
         , mC2( c2 )
         , mC2End{ c2end }
      {
      }

      value_type operator*() const noexcept
      {
         std::optional< typename Range::Iterator::value_type > a;
         if( mC1 != mC1End )
            a = *mC1;
         std::optional< typename Range::Iterator::value_type > b;
         if( mC2 != mC2End )
            b = *mC2;
         return { a, b };
      }

      Iterator operator++()
      {
         ++mC1;
         ++mC2;
         return *this;
      }

      bool operator!=( const Iterator& iterator ) const noexcept
      {
         return mC1 != iterator.mC1 || mC2 != iterator.mC2;
         return false;
      }

      typename Range::Iterator mC1;
      typename Range::Iterator mC1End;
      typename Range::Iterator mC2;
      typename Range::Iterator mC2End;
   };

   auto begin() const
   {
      return Iterator( std::begin( c1 ), std::end( c1 ), std::begin( c2 ), std::end( c2 ) );
   }

   auto end() const
   {
      return Iterator( std::end( c1 ), std::end( c1 ), std::end( c2 ), std::end( c2 ) );
   }
};

template< typename C1 >
zip_container< C1 > zip( C1& c1, C1& c2 )
{
   return zip_container< C1 >( c1, c2 );
}

static void match( const ISyntaxNodeSP& node, const SyntaxNodeEmptyVisitor::Handlers& handlers )
{
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
};

template< typename SourceNode, typename TargetNode, typename CreateRoot, typename CreateNode, typename GetChildrenReverseIterators >
TargetNode create_tree_from( const SourceNode& source_root, const CreateRoot& create_root, const CreateNode& create_node,
                             const GetChildrenReverseIterators& get_children_reverse_iterators )
{
   const auto& target_root = create_root( source_root );
   std::vector< std::pair< SourceNode, TargetNode > > stack;
   std::vector< std::reference_wrapper< const SourceNode > > source_search_path_stack;
   source_search_path_stack.emplace_back( source_root );
   stack.emplace_back( source_root, target_root );
   const auto& [ rbegin, rend ] = get_children_reverse_iterators( source_root );
   size_t root_children_size = std::distance( rbegin, rend );
   std::vector< std::reference_wrapper< const SourceNode > > source_root_children_forward_order( rbegin, rend );
   std::reverse( source_root_children_forward_order.begin(), source_root_children_forward_order.end() );
   for( const auto& child_of_root : source_root_children_forward_order )
   {
      iterative_dfs2(
         child_of_root,
         [ &target_root, &create_node, &stack, &source_search_path_stack ]( const SourceNode& node ) -> bool
         {
            source_search_path_stack.emplace_back( node );
            auto& [ source, target ] = stack.back();
            std::optional< std::reference_wrapper< TargetNode > > new_target_node = create_node( source_search_path_stack, target );
            if( new_target_node )
               stack.emplace_back( node, new_target_node.value() );
            return false;
         },
         [ &stack, &source_search_path_stack ]( const SourceNode& node )
         {
            source_search_path_stack.pop_back();
            auto& [ source, target ] = stack.back();
            if( source == node )
               stack.pop_back();
         },
         get_children_reverse_iterators );
   }
   auto& [ source, target ] = stack.back();
   return target;
}
