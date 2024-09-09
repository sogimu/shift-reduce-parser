#include "nonterminals/if_expression_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/scope_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"

IfExpressionSyntaxNode::IfExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::IF_EXPRESSION }
{
}
IfExpressionSyntaxNode::IfExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::IF_EXPRESSION }
{
   Add( conditional_expression );
   Add( scope );
}
void IfExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool IfExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.if_expression_syntax_node = [ this, &is_equal ]( const IfExpressionSyntaxNodeSP& node )
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

ConditionalExpressionSyntaxNodeSP IfExpressionSyntaxNode::conditional_expression() const
{
   return std::dynamic_pointer_cast< ConditionalExpressionSyntaxNode >( this->operator[]( 0 ) );
}

ScopeSyntaxNodeSP IfExpressionSyntaxNode::true_scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 1 ) );
}

ScopeSyntaxNodeSP IfExpressionSyntaxNode::false_scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 2 ) );
}
