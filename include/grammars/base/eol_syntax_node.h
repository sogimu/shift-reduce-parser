#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class EolSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this<EolSyntaxNode>
{
        public:
    EolSyntaxNode(): ISyntaxNode( Token_Type::EOL ) {}

    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;
};

using EolSyntaxNodeSP = std::shared_ptr<EolSyntaxNode>;
