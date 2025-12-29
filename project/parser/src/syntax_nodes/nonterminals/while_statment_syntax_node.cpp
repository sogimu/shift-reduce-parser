#include "nonterminals/while_statment_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include <cstddef>

WhileStatmentSyntaxNode::WhileStatmentSyntaxNode( const WhileStatmentSyntaxNode& while_statment_syntax_node )
   : ISyntaxNode{ Token_Type::WHILE_STATMENT }
{
   mTokens = while_statment_syntax_node.lexical_tokens();

}

WhileStatmentSyntaxNode::WhileStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::WHILE_STATMENT }
{
   mTokens = lexical_tokens;
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

// ConditionalExpressionSyntaxNodeSP WhileStatmentSyntaxNode::conditional_expression() const
// {
//    return std::dynamic_pointer_cast< ConditionalExpressionSyntaxNode >( this->operator[]( 0 ) );
// }

ScopeSyntaxNodeSP WhileStatmentSyntaxNode::scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 1 ) );
}

std::vector< LexicalTokens::LexicalToken > WhileStatmentSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
};
