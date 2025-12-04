#include "terminals/while_syntax_node.h"

#include "i_syntax_node_visitor.h"

WhileSyntaxNode::WhileSyntaxNode( const WhileSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::WHILE, node.lexical_tokens() }
{

}

WhileSyntaxNode::WhileSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::WHILE, token }
{

}

void WhileSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
