#include "terminals/equal_syntax_node.h"

#include "i_syntax_node_visitor.h"

void EqualSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
