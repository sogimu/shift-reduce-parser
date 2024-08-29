#include "base/semicolon_syntax_node.h"

#include "i_syntax_node_visitor.h"

SemicolonSyntaxNode::SemicolonSyntaxNode()
   : ISyntaxNode( Token_Type::SEMICOLON )
{
}

void SemicolonSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
