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
#include <utility>

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
   StackDFS( std::vector< std::pair< Node, bool > >& stack )
      : mStack{ stack }
   {
   }

   void push( const ISyntaxNodeSP& node, bool is_pre_order )
   {
      mStack.emplace_back( node, is_pre_order );
   }

   void push( const std::list< ISyntaxNodeSP >& nodes )
   {
      for( auto it = nodes.rbegin(); it != nodes.rend(); ++it )
      {
         const auto& child = *it;
         push( child, true );
      }
   }

   void pushChildrenOf( const ISyntaxNodeSP& node )
   {
      const auto& childern_value = node->Children();
      push( childern_value, true );
   }

   void popUntil( const ISyntaxNodeSP& target_node )
   {
      for( auto it = mStack.rbegin(); it != mStack.rend(); )
      {
         // auto& [ node, is_pre_order ] = stack.top();
         auto& [ node, is_pre_order ] = *it;
         if( node == target_node )
            break;
         if( is_pre_order )
         {
            it = decltype( it )( mStack.erase( std::next( it ).base() ) );
         }
         else
         {
            ++it;
         }
      }
   }

   bool empty() const
   {
      return mStack.empty();
   }

   auto top() const
   {
      return mStack.back();
   }
   void pop()
   {
      mStack.pop_back();
   }

private:
   std::vector< std::pair< Node, bool > >& mStack;
};

template< typename Node, typename PreFunc, typename PostFunc >
void iterative_managed_dfs( const Node& start, PreFunc pre_func, PostFunc post_func )
{
   std::vector< std::pair< Node, bool > > stack;

   StackDFS< Node > stack_dfs{ stack };
   stack_dfs.push( start, true );
   // stack.emplace( start, true );

   // while( !stack.empty() )
   while( !stack_dfs.empty() )
   {
      // auto& [ node, is_pre_order ] = stack.top();
      auto [ node, is_pre_order ] = stack_dfs.top();
      stack_dfs.pop();

      if( is_pre_order )
      {
         stack_dfs.push( node, false );
         /* const auto& children_opt =  */ pre_func( node, stack_dfs );
         // stack.emplace( node, false );
         // is_pre_order = false;

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
         // stack.pop();
         // stack_dfs.pop();
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

[[maybe_unused]] static void iterate_over_last_n_nodes( const Stack& stack, size_t n, const SyntaxNodeEmptyVisitor::Handlers& handlers )
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

[[maybe_unused]] static void match( const ISyntaxNodeSP& node, const SyntaxNodeEmptyVisitor::Handlers& handlers )
{
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
}

template< typename SourceNode, typename TargetNode, typename CreateRoot, typename CreateNode, typename GetChildrenReverseIterators >
TargetNode create_tree_from( const SourceNode& source_root, const CreateRoot& create_root, const CreateNode& create_node,
                             const GetChildrenReverseIterators& get_children_reverse_iterators )
{
   std::vector< std::pair< std::reference_wrapper< const SourceNode >, std::optional< std::reference_wrapper< TargetNode > > > > stack;
   stack.emplace_back( std::make_pair( std::cref( source_root ), std::optional< std::reference_wrapper< TargetNode > >{} ) );
   std::vector< std::reference_wrapper< const TargetNode > > source_stack;
   source_stack.emplace_back( std::cref( source_root ) );
   std::vector< std::reference_wrapper< TargetNode > > target_stack;
   auto target_root = create_root( source_root );
   target_stack.emplace_back( std::ref( target_root ) );
   stack.emplace_back( std::make_pair( std::cref( source_root ), std::optional< std::reference_wrapper< TargetNode > >{ std::ref( target_root ) } ) );
   const auto& [ rbegin, rend ] = get_children_reverse_iterators( source_root );
   // size_t root_children_size = std::distance( rbegin, rend );
   std::vector< std::reference_wrapper< const SourceNode > > source_root_children_forward_order( rbegin, rend );
   std::reverse( source_root_children_forward_order.begin(), source_root_children_forward_order.end() );
   for( const auto& child_of_root : source_root_children_forward_order )
   {
      iterative_dfs2(
         child_of_root,
         [ &create_node, &stack, &target_stack, &source_stack ]( const SourceNode& source_node ) -> bool
         {
            source_stack.emplace_back( std::cref( source_node ) );
            std::optional< std::reference_wrapper< TargetNode > > new_target_node_opt = create_node( source_stack, target_stack );
            stack.emplace_back( std::make_pair( std::cref( source_node ), new_target_node_opt ) );
            if( new_target_node_opt )
            {
               target_stack.emplace_back( new_target_node_opt.value() );
            }
            return false;
         },
         [ &stack, &source_stack, &target_stack ]( [[maybe_unused]] const SourceNode& source_node )
         {
            auto& [ source, target ] = stack.back();
            if( target )
            {
               target_stack.pop_back();
            }
            source_stack.pop_back();
            stack.pop_back();
         },
         get_children_reverse_iterators );
   }
   return target_root;
}

template< typename SourceNode, typename TargetNode, typename CreateRoot, typename CreateNodePre, typename CreateNodePost, typename GetChildrenReverseIterators >
TargetNode create_tree_from1( const SourceNode& source_root, const CreateRoot& create_root, const CreateNodePre& create_node_pre_func,
                              const CreateNodePost& create_node_on_post_func, const GetChildrenReverseIterators& get_children_reverse_iterators )
{
   std::vector< std::pair< std::reference_wrapper< const SourceNode >, std::optional< std::reference_wrapper< TargetNode > > > > stack;
   stack.emplace_back( std::make_pair( std::cref( source_root ), std::optional< std::reference_wrapper< TargetNode > >{} ) );
   std::vector< std::reference_wrapper< const TargetNode > > source_stack;
   source_stack.emplace_back( std::cref( source_root ) );
   std::vector< std::reference_wrapper< TargetNode > > target_stack;
   auto target_root = create_root( source_root );
   target_stack.emplace_back( std::ref( target_root ) );
   stack.emplace_back( std::make_pair( std::cref( source_root ), std::optional< std::reference_wrapper< TargetNode > >{ std::ref( target_root ) } ) );
   const auto& [ rbegin, rend ] = get_children_reverse_iterators( source_root );
   // size_t root_children_size = std::distance( rbegin, rend );
   std::vector< std::reference_wrapper< const SourceNode > > source_root_children_forward_order( rbegin, rend );
   std::reverse( source_root_children_forward_order.begin(), source_root_children_forward_order.end() );
   for( const auto& child_of_root : source_root_children_forward_order )
   {
      iterative_dfs2(
         child_of_root,
         [ &create_node_pre_func, &stack, &target_stack, &source_stack ]( const SourceNode& source_node ) -> bool
         {
            source_stack.emplace_back( std::cref( source_node ) );
            std::optional< std::reference_wrapper< TargetNode > > new_target_node_opt = create_node_pre_func( source_stack, target_stack );
            stack.emplace_back( std::make_pair( std::cref( source_node ), new_target_node_opt ) );
            if( new_target_node_opt )
            {
               target_stack.emplace_back( new_target_node_opt.value() );
            }
            return false;
         },
         [ &create_node_on_post_func, &stack, &source_stack, &target_stack ]( [[maybe_unused]] const SourceNode& source_node )
         {
            const auto& [ source, target ] = stack.back();
            if( !target )
            {
               [[maybe_unused]] std::optional< std::reference_wrapper< TargetNode > > new_target_node_opt = create_node_on_post_func( source_stack, target_stack );
               // target = new_target_node_opt;
            }
            if( target )
            {
               target_stack.pop_back();
            }
            source_stack.pop_back();
            stack.pop_back();
         },
         get_children_reverse_iterators );
   }
   return target_root;
}

namespace
{
template< typename T >
class SyntaxNodeCheckTypeVisitor : public ISyntaxNodeVisitor
{
public:
   ~SyntaxNodeCheckTypeVisitor() = default;

   void visit( const BolSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, BolSyntaxNode > )
         mResult = true;
   }

   void visit( const EolSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, EolSyntaxNode > )
         mResult = true;
   }

   void visit( const PlusSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, PlusSyntaxNode > )
         mResult = true;
   }

   void visit( const MinusSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, MinusSyntaxNode > )
         mResult = true;
   }

   void visit( const AsteriskSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, AsteriskSyntaxNode > )
         mResult = true;
   }
   void visit( const SlashSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, SlashSyntaxNode > )
         mResult = true;
   }

   void visit( const NumberSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, NumberSyntaxNode > )
         mResult = true;
   }

   void visit( const FSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, FSyntaxNode > )
         mResult = true;
   }

   void visit( const AdditionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, AdditionSyntaxNode > )
         mResult = true;
   }

   void visit( const SubtractionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, SubtractionSyntaxNode > )
         mResult = true;
   }
   void visit( const MultiplySyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, MultiplySyntaxNode > )
         mResult = true;
   }
   void visit( const DivisionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, DivisionSyntaxNode > )
         mResult = true;
   }

   void visit( const SemicolonSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, SemicolonSyntaxNode > )
         mResult = true;
   }

   void visit( const ExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ExpressionSyntaxNode > )
         mResult = true;
   }

   void visit( const ScopeSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ScopeSyntaxNode > )
         mResult = true;
   }

   void visit( const OpenCurlyBracketSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, OpenCurlyBracketSyntaxNode > )
         mResult = true;
   }

   void visit( const CloseCurlyBracketSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, CloseCurlyBracketSyntaxNode > )
         mResult = true;
   }

   void visit( const OpenCircleBracketSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, OpenCircleBracketSyntaxNode > )
         mResult = true;
   }

   void visit( const CloseCircleBracketSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, CloseCircleBracketSyntaxNode > )
         mResult = true;
   }

   void visit( const ComputationalExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ComputationalExpressionSyntaxNode > )
         mResult = true;
   }

   void visit( const VaribleSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, VaribleSyntaxNode > )
         mResult = true;
   }

   void visit( const ConditionalExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ConditionalExpressionSyntaxNode > )
         mResult = true;
   }

   void visit( const PrintExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, PrintExpressionSyntaxNode > )
         mResult = true;
   }

   void visit( const VaribleAssigmentSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, VaribleAssigmentSyntaxNode > )
         mResult = true;
   }

   void visit( const NameSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, NameSyntaxNode > )
         mResult = true;
   }

   void visit( const CommaSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, CommaSyntaxNode > )
         mResult = true;
   }

   void visit( const PrintSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, PrintSyntaxNode > )
         mResult = true;
   }

   void visit( const EqualSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, EqualSyntaxNode > )
         mResult = true;
   }

   void visit( const LessSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, LessSyntaxNode > )
         mResult = true;
   }

   void visit( const MoreSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, MoreSyntaxNode > )
         mResult = true;
   }

   void visit( const IfSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, IfSyntaxNode > )
         mResult = true;
   }

   void visit( const IfExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, IfExpressionSyntaxNode > )
         mResult = true;
   }
   void visit( const WhileSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, WhileSyntaxNode > )
         mResult = true;
   }

   void visit( const WhileExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, WhileExpressionSyntaxNode > )
         mResult = true;
   }

   void visit( const FunctionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, FunctionSyntaxNode > )
         mResult = true;
   }

   void visit( const FunctionCallSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, FunctionCallSyntaxNode > )
         mResult = true;
   }

   void visit( const ReturnSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ReturnSyntaxNode > )
         mResult = true;
   }

   void visit( const ReturnExpressionSyntaxNodeSP& /* node */ ) override
   {
      if constexpr( std::is_same_v< T, ReturnExpressionSyntaxNode > )
      {

         mResult = true;
      }
   }

   bool result() const
   {
      return mResult;
   }

private:
   bool mResult = false;
};
} // namespace

template< typename T >
static bool check_type( const ISyntaxNodeSP& node )
{
   const auto& visitor = std::make_shared< SyntaxNodeCheckTypeVisitor< T > >();
   node->accept( visitor );
   return visitor->result();
}
