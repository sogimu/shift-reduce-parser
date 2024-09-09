#include "nonterminals/print_expression_syntax_node.h"

#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
}

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression )
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
   Add( computational_expression );
}

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode( const NameSyntaxNodeSP& name_syntax_node )
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
   Add( name_syntax_node );
}

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode( const ISyntaxNodeSP& argument )
   : ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
   Add( argument );
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

   return is_equal;
}

ComputationalExpressionSyntaxNodeSP PrintExpressionSyntaxNode::computational_expression() const
{
   ComputationalExpressionSyntaxNodeSP argument;
   const auto& value_node = this->operator[]( 0 );
   match( value_node,
          { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
            { argument = computational_expression; },
            .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
   return argument;
}
