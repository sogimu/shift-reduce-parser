#include "terminals/semicolon_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

SemicolonSyntaxNode::SemicolonSyntaxNode( const SemicolonSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::SEMICOLON, node.lexical_tokens() }
{
}

SemicolonSyntaxNode::SemicolonSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::SEMICOLON, token }
{
}

void SemicolonSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool SemicolonSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.semicolon_syntax_node = [ this, &is_equal ]( const SemicolonSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}
