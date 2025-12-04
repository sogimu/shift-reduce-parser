#include "terminals/if_syntax_node.h"

#include "i_syntax_node_visitor.h"

IfSyntaxNode::IfSyntaxNode( const IfSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::IF, node.lexical_tokens() }
{

}

IfSyntaxNode::IfSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::IF, token }
{

}

void IfSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
