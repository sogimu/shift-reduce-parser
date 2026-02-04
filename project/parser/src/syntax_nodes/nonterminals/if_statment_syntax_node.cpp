#include "nonterminals/if_statment_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include <stdexcept>
IfStatmentSyntaxNode::IfStatmentSyntaxNode( const IfStatmentSyntaxNode& if_statment_syntax_node )
   : ISyntaxNode{ Token_Type::IF_STATMENT }
   , mConditionalExpression{ if_statment_syntax_node.mConditionalExpression }
   , mTokens{ if_statment_syntax_node.lexical_tokens() }
{
}

IfStatmentSyntaxNode::IfStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& true_scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::IF_STATMENT }
   , mConditionalExpression{ conditional_expression }
{
   mTokens = lexical_tokens;
   add_back( conditional_expression );
   add_back( true_scope );
}

IfStatmentSyntaxNode::IfStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& true_scope, const ScopeSyntaxNodeSP& false_scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::IF_STATMENT }
   , mConditionalExpression{ conditional_expression }
{
   mTokens = lexical_tokens;
   add_back( conditional_expression );
   add_back( true_scope );
   if( false_scope )
       add_back( false_scope );
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

ISyntaxNodeSP IfStatmentSyntaxNode::conditional_expression() const
{
   return mConditionalExpression;
}

ScopeSyntaxNodeSP IfStatmentSyntaxNode::true_scope() const
{
   const auto& true_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( *std::next(rbegin()) );
   if( !true_scope )
      throw std::runtime_error( "True scope not found in if statment" );
   return true_scope;
}

ScopeSyntaxNodeSP IfStatmentSyntaxNode::false_scope() const
{
   const auto& false_scope = std::dynamic_pointer_cast< ScopeSyntaxNode >( *rbegin() );
   if( !false_scope )
      throw std::runtime_error( "False scope not found in if statment" );
   return false_scope;
}

std::vector< LexicalTokens::LexicalToken > IfStatmentSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
};
