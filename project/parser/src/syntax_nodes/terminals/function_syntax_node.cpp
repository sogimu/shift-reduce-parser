#include "terminals/function_syntax_node.h"

#include "i_syntax_node_visitor.h"

FunctionSyntaxNode::FunctionSyntaxNode( const FunctionSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::FUNCTION, node.lexical_tokens() }
{

}

FunctionSyntaxNode::FunctionSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::FUNCTION, token }
{

}
void FunctionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
