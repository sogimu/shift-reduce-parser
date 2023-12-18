    #pragma once

#include <vector>
#include <string>
#include <memory>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class MoreSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<MoreSyntaxNode>
{
public:
    MoreSyntaxNode()
        : ISyntaxNode(Token_Type::MORE)
    {
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

};

using MoreSyntaxNodeSP = std::shared_ptr<MoreSyntaxNode>;
