#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>
#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class MoreSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this<MoreSyntaxNode>
{
        public:
    MoreSyntaxNode(): ISyntaxNode( Token_Type::MORE ) {}

    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;
};

using MoreSyntaxNodeSP = std::shared_ptr<MoreSyntaxNode>;
using MoreSyntaxNodeCSP = std::shared_ptr<const MoreSyntaxNode>;
