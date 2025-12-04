#include "nonterminals/if_statment_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include <stdexcept>
IfStatmentSyntaxNode::IfStatmentSyntaxNode( const IfStatmentSyntaxNode& if_statment_syntax_node )
   : ISyntaxNode{ if_statment_syntax_node }
{
   mTokens = if_statment_syntax_node.lexical_tokens();
}

IfStatmentSyntaxNode::IfStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::IF_STATMENT }
{
   mTokens = lexical_tokens;
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
      if( node->lexical_tokens() != this->lexical_tokens() )
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

// ConditionalExpressionSyntaxNodeSP IfStatmentSyntaxNode::conditional_expression() const
// {
//    return std::dynamic_pointer_cast< ConditionalExpressionSyntaxNode >( this->operator[]( 0 ) );
// }

ScopeSyntaxNodeSP IfStatmentSyntaxNode::true_scope() const
{
   const auto& true_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( *rbegin() );
   if( !true_scope )
      throw std::runtime_error( "True scope not found in if expression" );
   return true_scope;
}

ScopeSyntaxNodeSP IfStatmentSyntaxNode::false_scope() const
{
   const auto& false_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( *std::next(rbegin()) );
   if( !false_scope )
      throw std::runtime_error( "False scope not found in if expression" );
   return false_scope;
}

std::vector< LexicalTokens::LexicalToken > IfStatmentSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
};
