#include "terminals/var_syntax_node.h"

#include "i_syntax_node_visitor.h"

VarSyntaxNode::VarSyntaxNode( const VarSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::VAR, node.lexical_tokens() }
{

}

VarSyntaxNode::VarSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::VAR, token }
{

}

void VarSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
