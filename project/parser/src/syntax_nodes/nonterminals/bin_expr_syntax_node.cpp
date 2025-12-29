#include "nonterminals/bin_expr_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "make_shallow_syntax_node_copy.h"

#include <vector>

BinExprSyntaxNode::BinExprSyntaxNode( const BinExprSyntaxNode& bin_expr_syntax_node )
   : ISyntaxNode{ Token_Type::BinExpr }
   , mType{ bin_expr_syntax_node.type() }
{
   mTokens = bin_expr_syntax_node.lexical_tokens();
   // for( const auto& child : mChildren )
   // {
   //     add_back( make_shallow_copy( child ) );
   // }
}

BinExprSyntaxNode::BinExprSyntaxNode( const Type& type )
   : ISyntaxNode{ Token_Type::BinExpr }
   , mType{ type }
{
}

BinExprSyntaxNode::BinExprSyntaxNode( const Type& type, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::BinExpr }
   , mType{ type }
{
   mTokens = lexical_tokens;
}

BinExprSyntaxNode::BinExprSyntaxNode( const Type& type, const ISyntaxNodeSP& arg0, const ISyntaxNodeSP& arg1, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::BinExpr }
   , mType{ type }
{
   add_back( arg0 );
   add_back( arg1 );

   mTokens = lexical_tokens;
}

BinExprSyntaxNode::Type BinExprSyntaxNode::type() const
{
  return mType;
}

bool BinExprSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.bin_expr_syntax_node = [ this, &is_equal ]( const BinExprSyntaxNodeSP& node )
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
      if( node->type() != this->type() )
        return;
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

void BinExprSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

std::vector< LexicalTokens::LexicalToken > BinExprSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
};
void BinExprSyntaxNode::add_lexical_token(const LexicalTokens::LexicalToken& token)
{
  mTokens.push_back( token );
}
