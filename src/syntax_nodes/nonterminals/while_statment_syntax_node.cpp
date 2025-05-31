#include "nonterminals/while_statment_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include <cstddef>

WhileStatmentSyntaxNode::WhileStatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::WHILE_STATMENT }
{
}
WhileStatmentSyntaxNode::WhileStatmentSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::WHILE_STATMENT }
{
   add_back( conditional_expression );
   add_back( scope );
}
WhileStatmentSyntaxNode::WhileStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::WHILE_STATMENT }
{
   add_back( conditional_expression );
   add_back( scope );
}
void WhileStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool WhileStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.while_statment_syntax_node = [ this, &is_equal ]( const WhileStatmentSyntaxNodeSP& node )
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

ConditionalExpressionSyntaxNodeSP WhileStatmentSyntaxNode::conditional_expression() const
{
   return std::dynamic_pointer_cast< ConditionalExpressionSyntaxNode >( this->operator[]( 0 ) );
}

ScopeSyntaxNodeSP WhileStatmentSyntaxNode::scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 1 ) );
}
