#include "nonterminals/if_statment_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include <stdexcept>

IfStatmentSyntaxNode::IfStatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::IF_STATMENT }
{
}
IfStatmentSyntaxNode::IfStatmentSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::IF_STATMENT }
{
   add_back( conditional_expression );
   add_back( scope );
}
void IfStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool IfStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.if_statment_syntax_node = [ this, &is_equal ]( const IfStatmentSyntaxNodeSP& node )
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

ConditionalExpressionSyntaxNodeSP IfStatmentSyntaxNode::conditional_expression() const
{
   return std::dynamic_pointer_cast< ConditionalExpressionSyntaxNode >( this->operator[]( 0 ) );
}

ScopeSyntaxNodeSP IfStatmentSyntaxNode::true_scope() const
{
   const auto& true_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 0 ) );
   if( !true_scope )
      throw std::runtime_error( "True scope not found in if expression" );
   return true_scope;
}

ScopeSyntaxNodeSP IfStatmentSyntaxNode::false_scope() const
{
   const auto& false_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 1 ) );
   if( !false_scope )
      throw std::runtime_error( "False scope not found in if expression" );
   return false_scope;
}
