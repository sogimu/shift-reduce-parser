#pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class CloseCurlyBracketSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<CloseCurlyBracketSyntaxNode>
{
public:
    CloseCurlyBracketSyntaxNode()
        : ISyntaxNode(Token_Type::CLOSE_CURLY_BRACKET)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using CloseCurlyBracketSyntaxNodeSP = std::shared_ptr<CloseCurlyBracketSyntaxNode>;
