#pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class OpenCurlyBracketSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<OpenCurlyBracketSyntaxNode>
{
public:
    OpenCurlyBracketSyntaxNode()
        : ISyntaxNode(Token_Type::OPEN_CURLY_BRACKET)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using OpenCurlyBracketSyntaxNodeSP = std::shared_ptr<OpenCurlyBracketSyntaxNode>;
