#include "computational_expression_syntax_node.h"

#include "conditional_expression_syntax_node.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

void ComputationalExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ComputationalExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.computational_expression_syntax_node = [ this, &is_equal ]( const ComputationalExpressionSyntaxNodeSP& node )
   {
      if( node->Children().size() == this->Children().size() )
      {
         is_equal = true;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   // node.accept( visitor );
   return is_equal;
}
