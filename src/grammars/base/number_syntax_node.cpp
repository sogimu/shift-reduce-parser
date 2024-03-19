#include "base/number_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

#include <string>
#include <vector>

void NumberSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }
