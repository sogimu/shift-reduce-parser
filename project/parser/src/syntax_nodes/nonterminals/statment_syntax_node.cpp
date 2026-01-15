#include "nonterminals/statment_syntax_node.h"

#include <vector>

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "make_shallow_syntax_node_copy.h"

StatmentSyntaxNode::StatmentSyntaxNode( const StatmentSyntaxNode& statment_syntax_node )
  : ISyntaxNode{ Token_Type::STATMENT }
  , mTokens{ statment_syntax_node.mTokens }
{
}

StatmentSyntaxNode::StatmentSyntaxNode( const ISyntaxNodeSP& syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( syntax_node );
}

StatmentSyntaxNode::StatmentSyntaxNode( const LexicalTokens::LexicalToken& semicolon_lexical_token )
{
   mTokens = { semicolon_lexical_token };
}

StatmentSyntaxNode::StatmentSyntaxNode( const ISyntaxNodeSP& syntax_node, const LexicalTokens::LexicalToken& semicolon_lexical_token )
{
   add_back( syntax_node );
   mTokens = { semicolon_lexical_token };
}

void StatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool StatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.statment_syntax_node = [ this, &is_equal ]( const StatmentSyntaxNodeSP& node )
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

std::vector< LexicalTokens::LexicalToken > StatmentSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
};
void StatmentSyntaxNode::add_lexical_token(const LexicalTokens::LexicalToken& token)
{
  mTokens.push_back( token );
}
