#include "terminals/return_syntax_node.h"

#include "i_syntax_node_visitor.h"

ReturnSyntaxNode::ReturnSyntaxNode()
   : ISyntaxNode( Token_Type::SEMICOLON )
{
}

void ReturnSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
