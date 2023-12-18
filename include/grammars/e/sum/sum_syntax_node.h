#pragma once

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "base/f_syntax_node.h"

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr<ComputationalExpressionSyntaxNode>;

class SumSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<SumSyntaxNode>

{
public:
    SumSyntaxNode(const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1);
    SumSyntaxNode(const ComputationalExpressionSyntaxNodeSP& computational_expression0, const ComputationalExpressionSyntaxNodeSP& computational_expression1);

    std::vector<FSyntaxNodeSP> Arguments() const;

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using SumSyntaxNodeSP = std::shared_ptr<SumSyntaxNode>;
