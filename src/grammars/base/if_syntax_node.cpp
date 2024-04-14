#include "base/if_syntax_node.h"

#include "i_syntax_node_visitor.h"

void IfSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
