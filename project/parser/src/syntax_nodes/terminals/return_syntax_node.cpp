#include "terminals/return_syntax_node.h"

#include "enums.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

ReturnSyntaxNode::ReturnSyntaxNode( const ReturnSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::RETURN, node.lexical_tokens() }
{
}

ReturnSyntaxNode::ReturnSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::RETURN, token }
{
}

void ReturnSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ReturnSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.return_syntax_node = [ this, &is_equal ]( const ReturnSyntaxNodeSP& node )
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
