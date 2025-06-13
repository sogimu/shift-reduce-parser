#pragma once

#include "syntax_node_empty_visitor.h"

#include <memory>

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
   for( const auto& node : last_n_syntax_nodes( stack, n ) )
   {
      node->accept( visitor );
   }
}
