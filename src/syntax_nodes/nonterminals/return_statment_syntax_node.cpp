#include "nonterminals/return_statment_syntax_node.h"

#include "is_last_nodes.h"
#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

ReturnStatmentSyntaxNode::ReturnStatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::RETURN_STATMENT }
{
}

ReturnStatmentSyntaxNode::ReturnStatmentSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression )
   : ISyntaxNode{ Token_Type::RETURN_STATMENT }
{
   add_back( computational_expression );
}

ReturnStatmentSyntaxNode::ReturnStatmentSyntaxNode( const ISyntaxNodeSP& argument )
   : ISyntaxNode{ Token_Type::RETURN_STATMENT }
{
   ISyntaxNodeSP child = argument;

   if( IsNode< NameSyntaxNode >( argument ) )
   {
      const auto& name_node = std::dynamic_pointer_cast< NameSyntaxNode >( argument );
      child = std::make_shared< VaribleSyntaxNode >( name_node->value() );
   }

   add_back( child );
}

void ReturnStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ReturnStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.return_statment_syntax_node = [ this, &is_equal ]( const ReturnStatmentSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      for( size_t i = 0; i < Children().size(); ++i )
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

ComputationalExpressionSyntaxNodeSP ReturnStatmentSyntaxNode::computational_expression() const
{
   ComputationalExpressionSyntaxNodeSP argument;
   const auto& value_node = this->operator[]( 0 );
   match( value_node,
          { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
            { argument = computational_expression; },
            .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
   return argument;
}
