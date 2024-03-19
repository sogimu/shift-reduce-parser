#include "print_expression_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>
#include <vector>

PrintExpressionSyntaxNode::PrintExpressionSyntaxNode(
    const ComputationalExpressionSyntaxNodeSP& computational_expression ):
    ISyntaxNode{ Token_Type::PRINT_EXPRESSION }
{
    Add( computational_expression );
}

void PrintExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }

ComputationalExpressionSyntaxNodeSP PrintExpressionSyntaxNode::computational_expression() const
{
    return std::dynamic_pointer_cast<ComputationalExpressionSyntaxNode>( this->operator[]( 0 ) );
}
