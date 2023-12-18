#include "expression_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

void ExpressionSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}
