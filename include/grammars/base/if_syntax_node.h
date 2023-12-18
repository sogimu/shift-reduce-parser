#pragma once

#include <vector>
#include <string>
#include <memory>

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class IfSyntaxNode :
    public ISyntaxNode,
    public std::enable_shared_from_this<IfSyntaxNode>
{
public:
    IfSyntaxNode()
        : ISyntaxNode(Token_Type::IF)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using IfSyntaxNodeSP = std::shared_ptr<IfSyntaxNode>;
