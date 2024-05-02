#include "print_expression_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
}

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode(
   const ComputationalExpressionSyntaxNodeSP& computational_expression )
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
   Add( computational_expression );
}

void PrintExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool PrintExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.print_expression_syntax_node = [ this, &is_equal ]( const PrintExpressionSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      for( int i = 0; i < Children().size(); ++i )
      {
         const auto& lft_child = ( *this )[ i ];
         const auto& rht_child = ( *node )[ i ];
         if( !lft_child->compare( *rht_child ) )
         {
            return;
         }
      }
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   // node.accept( visitor );
   return is_equal;
}
ComputationalExpressionSyntaxNodeSP PrintExpressionSyntaxNode::computational_expression() const
{
   return std::dynamic_pointer_cast< ComputationalExpressionSyntaxNode >( this->operator[]( 0 ) );
}
