#include "if_expression_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

void IfExpressionSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}

ConditionalExpressionSyntaxNodeSP IfExpressionSyntaxNode::conditional_expression() const
{
    return std::dynamic_pointer_cast<ConditionalExpressionSyntaxNode>( this->operator[](0) );
}

ScopeSyntaxNodeSP IfExpressionSyntaxNode::true_scope() const
{
    return std::dynamic_pointer_cast<ScopeSyntaxNode>( this->operator[](1) );
}

ScopeSyntaxNodeSP IfExpressionSyntaxNode::false_scope() const
{
    return std::dynamic_pointer_cast<ScopeSyntaxNode>( this->operator[](2) );
}
