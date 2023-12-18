#include "base/name_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

NameSyntaxNode::NameSyntaxNode(const std::string& value)
    : ISyntaxNode{Token_Type::NAME}
    , mValue{ value }
{
}

void NameSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}

std::string NameSyntaxNode::value() const
{
    return mValue;
}
