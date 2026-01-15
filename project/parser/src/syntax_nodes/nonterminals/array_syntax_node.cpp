#include "nonterminals/array_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "make_shallow_syntax_node_copy.h"
#include "syntax_node_empty_visitor.h"

ArraySyntaxNode::ArraySyntaxNode( const ArraySyntaxNode& scope )
   : ISyntaxNode{ Token_Type::ARRAY }
{
   mTokens = scope.lexical_tokens();
}

ArraySyntaxNode::ArraySyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::ARRAY }
{
   mTokens = lexical_tokens;
   add_back( expression );
}

ArraySyntaxNode::ArraySyntaxNode( const std::vector< ISyntaxNodeSP >& expressions, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::ARRAY }
{
   mTokens = lexical_tokens;
   for( const auto& expression : expressions )
      add_back( expression );
}
void ArraySyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

std::vector< LexicalTokens::LexicalToken > ArraySyntaxNode::lexical_tokens() const
{ 
    return mTokens; 
}

bool ArraySyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.array_syntax_node = [ this, &is_equal ]( const ArraySyntaxNodeSP& node )
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
