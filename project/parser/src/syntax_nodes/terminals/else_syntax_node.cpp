#include "terminals/else_syntax_node.h"

#include "i_syntax_node_visitor.h"

ElseSyntaxNode::ElseSyntaxNode( const ElseSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::IF, node.lexical_tokens() }
{

}

ElseSyntaxNode::ElseSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::IF, token }
{

}

void ElseSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
