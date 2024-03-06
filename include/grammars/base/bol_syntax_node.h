#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class BolSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this<BolSyntaxNode>
{
        public:
    BolSyntaxNode(): ISyntaxNode( Token_Type::BOL ) {}

    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;
};

using BolSyntaxNodeSP = std::shared_ptr<BolSyntaxNode>;
