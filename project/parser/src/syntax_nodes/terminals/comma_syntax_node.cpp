#include "terminals/comma_syntax_node.h"

#include "i_syntax_node_visitor.h"

CommaSyntaxNode::CommaSyntaxNode( const CommaSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::COMMA, node.lexical_tokens() }
{

}

CommaSyntaxNode::CommaSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::COMMA, token }
{

}

void CommaSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
