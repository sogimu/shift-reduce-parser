#pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class SemicolonSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<SemicolonSyntaxNode>
{
public:
    SemicolonSyntaxNode()
        : ISyntaxNode(Token_Type::SEMICOLON)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using SemicolonSyntaxNodeSP = std::shared_ptr<SemicolonSyntaxNode>;
