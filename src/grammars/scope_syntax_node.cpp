#include "scope_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

void ScopeSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}
