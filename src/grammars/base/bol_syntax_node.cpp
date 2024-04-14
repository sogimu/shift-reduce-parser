#include "base/bol_syntax_node.h"

#include "i_syntax_node_visitor.h"

void BolSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
