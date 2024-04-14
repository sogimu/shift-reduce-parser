#include "base/less_syntax_node.h"

#include "i_syntax_node_visitor.h"

void LessSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
