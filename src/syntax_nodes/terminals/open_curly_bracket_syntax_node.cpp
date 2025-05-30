#include "terminals/open_curly_bracket_syntax_node.h"

#include "i_syntax_node_visitor.h"

void OpenCurlyBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}
