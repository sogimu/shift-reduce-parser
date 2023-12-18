#pragma once

#include <vector>
#include <string>
#include "enums.h"
#include "i_syntax_node.h"
#include "sum/sum_syntax_node.h"
//#include "E/number_syntax_node.h"
//#include "i_syntax_node_visitor.h"

class ISyntaxNodeVisitor;

class ESyntaxNode :
    public ISyntaxNode,
    public std::enable_shared_from_this<ESyntaxNode>

{
public:
    ESyntaxNode(const SumSyntaxNodeSP& sum)
        : ISyntaxNode{Token_Type::E}
    {
        Add(sum);
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;
};

using ESyntaxNodeSP = std::shared_ptr<ESyntaxNode>;
