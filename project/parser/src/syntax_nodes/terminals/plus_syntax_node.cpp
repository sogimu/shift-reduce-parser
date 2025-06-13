#include "terminals/plus_syntax_node.h"

#include "i_syntax_node_visitor.h"

void PlusSyntaxNode::accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor )
{
   visitor->visit( shared_from_this() );
}
