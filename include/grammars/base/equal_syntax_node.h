#pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class EqualSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<EqualSyntaxNode>
{
public:
    EqualSyntaxNode()
        : ISyntaxNode(Token_Type::EQUAL)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using EqualSyntaxNodeSP = std::shared_ptr<EqualSyntaxNode>;
