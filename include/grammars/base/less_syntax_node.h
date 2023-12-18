#pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class LessSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<LessSyntaxNode>
{
public:
    LessSyntaxNode()
        : ISyntaxNode(Token_Type::LESS)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using LessSyntaxNodeSP = std::shared_ptr<LessSyntaxNode>;
