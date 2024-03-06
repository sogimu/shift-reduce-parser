#include "varible_assigment_syntax_node.h"

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "base/name_syntax_node.h"
#include "computational_expression_syntax_node.h"

VaribleAssigmentSyntaxNode::VaribleAssigmentSyntaxNode(const NameSyntaxNodeSP& name, const ComputationalExpressionSyntaxNodeSP& node)
    : ISyntaxNode{Token_Type::VARIBLE_ASSIGMENT}
{
    Add( node );
    Add( name );
}

std::string VaribleAssigmentSyntaxNode::name() const
{
    return std::dynamic_pointer_cast<NameSyntaxNode>( this->operator[](0) )->value();
}

ComputationalExpressionSyntaxNodeSP VaribleAssigmentSyntaxNode::computational_expression() const
{
    return std::dynamic_pointer_cast<ComputationalExpressionSyntaxNode>( this->operator[](1) );
}

void VaribleAssigmentSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}
