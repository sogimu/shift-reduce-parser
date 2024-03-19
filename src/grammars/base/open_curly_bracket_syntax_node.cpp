#include "base/open_curly_bracket_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

#include <string>
#include <vector>

void OpenCurlyBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }
