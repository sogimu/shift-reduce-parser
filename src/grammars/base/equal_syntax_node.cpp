#include "base/equal_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

#include <string>
#include <vector>

void EqualSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }
