#include "terminals/bol_syntax_node.h"

#include "i_syntax_node_visitor.h"

BolSyntaxNode::BolSyntaxNode( const BolSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::BOL, node.lexical_tokens() }
{
}

BolSyntaxNode::BolSyntaxNode( LexicalTokens::LexicalToken token )
  : ITerminalSyntaxNode{ Token_Type::BOL, token }
{
}
void BolSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
