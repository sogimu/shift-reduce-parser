#include "nonterminals/scope_statment_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "make_shallow_syntax_node_copy.h"
#include "syntax_node_empty_visitor.h"

ScopeSyntaxNode::ScopeSyntaxNode( const ScopeSyntaxNode& scope )
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
   mTokens = scope.lexical_tokens();
   // for( const auto& child : scope )
   // {
   //    add_back( make_shallow_copy( child ) );
   // }
}

ScopeSyntaxNode::ScopeSyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
   mTokens = lexical_tokens;
   add_back( expression );
}

ScopeSyntaxNode::ScopeSyntaxNode( const std::vector< ISyntaxNodeSP >& expressions, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
   mTokens = lexical_tokens;
   for( const auto& expression : expressions )
      add_back( expression );
}
void ScopeSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

std::vector< LexicalTokens::LexicalToken > ScopeSyntaxNode::lexical_tokens() const
{ 
    return mTokens; 
}

bool ScopeSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.scope_statment_syntax_node = [ this, &is_equal ]( const ScopeSyntaxNodeSP& node )
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
