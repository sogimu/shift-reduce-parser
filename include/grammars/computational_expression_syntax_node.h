#pragma once

#include "base/f_syntax_node.h"
#include "base/name_syntax_node.h"
#include "conditional_expression_syntax_node.h"
#include "e/e_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class ComputationalExpressionSyntaxNode : public ISyntaxNode,
                                          public std::enable_shared_from_this<ComputationalExpressionSyntaxNode>

{
        public:
    ComputationalExpressionSyntaxNode() = default;
    ComputationalExpressionSyntaxNode( const ESyntaxNodeSP& e ): ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
    {
        Add( e );
    }

    ComputationalExpressionSyntaxNode( const FSyntaxNodeSP& e ): ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
    {
        Add( e );
    }

    ComputationalExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node ):
        ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
    {
        Add( conditional_expression_syntax_node );
    }

    ComputationalExpressionSyntaxNode( const NameSyntaxNodeSP& name_syntax_node ):
        ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
    {
        Add( name_syntax_node );
    }
    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;
    bool compare( const ISyntaxNode& node ) const override;
};

using ComputationalExpressionSyntaxNodeSP = std::shared_ptr<ComputationalExpressionSyntaxNode>;
using ComputationalExpressionSyntaxNodeCSP = std::shared_ptr<const ComputationalExpressionSyntaxNode>;
