#include "base/close_curly_bracket_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

void CloseCurlyBracketSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}
