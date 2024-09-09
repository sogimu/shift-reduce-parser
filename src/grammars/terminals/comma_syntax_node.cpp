#include "terminals/comma_syntax_node.h"

#include "i_syntax_node_visitor.h"

CommaSyntaxNode::CommaSyntaxNode()
   : ISyntaxNode( Token_Type::COMMA )
{
}

void CommaSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
