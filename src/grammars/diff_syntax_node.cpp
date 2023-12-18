#include "e/diff/diff_syntax_node.h"

#include <vector>
#include <string>
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

std::vector<FSyntaxNodeSP> DiffSyntaxNode::Arguments() const
{
    std::vector<FSyntaxNodeSP> result;
    SyntaxNodeEmptyVisitor::Handlers handlers;
    handlers.f_syntax_node = [&result](const FSyntaxNodeSP& node)
    {
        result.emplace_back(node);
    };

    const auto& visitor = std::make_shared<SyntaxNodeEmptyVisitor>( handlers );
    for( const auto& child : this->Children() )
    {
        child->accept(visitor);
    }
    return result;
}

void DiffSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}
