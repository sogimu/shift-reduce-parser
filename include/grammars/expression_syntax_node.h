#pragma once

#include "computational_expression_syntax_node.h"
#include "conditional_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "if_expression_syntax_node.h"
#include "print_expression_syntax_node.h"
#include "varible_assigment_syntax_node.h"

#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class ExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this<ExpressionSyntaxNode>
{
        public:
    ExpressionSyntaxNode() = default;
    ExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression_syntax_node ):
        ISyntaxNode{ Token_Type::EXPRESSION }
    {
        Add( computational_expression_syntax_node );
    }

    ExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node ):
        ISyntaxNode{ Token_Type::EXPRESSION }
    {
        Add( conditional_expression_syntax_node );
    }

    ExpressionSyntaxNode( const IfExpressionSyntaxNodeSP& if_expression_syntax_node ):
        ISyntaxNode{ Token_Type::EXPRESSION }
    {
        Add( if_expression_syntax_node );
    }

    ExpressionSyntaxNode( const PrintExpressionSyntaxNodeSP& print_expression_syntax_node ):
        ISyntaxNode{ Token_Type::EXPRESSION }
    {
        Add( print_expression_syntax_node );
    }

    ExpressionSyntaxNode( const VaribleAssigmentSyntaxNodeSP& varible_assigment_syntax_node ):
        ISyntaxNode{ Token_Type::EXPRESSION }
    {
        Add( varible_assigment_syntax_node );
    }

    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;

    bool compare( const ISyntaxNode& node ) const override;
};

using ExpressionSyntaxNodeSP = std::shared_ptr<ExpressionSyntaxNode>;
using ExpressionSyntaxNodeCSP = std::shared_ptr<const ExpressionSyntaxNode>;
