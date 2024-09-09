#include "terminals/close_circle_bracket_syntax_node.h"

#include "i_syntax_node_visitor.h"

void CloseCircleBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}