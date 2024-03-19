#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>
#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class OpenCircleBracketSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this<OpenCircleBracketSyntaxNode>
{
        public:
    OpenCircleBracketSyntaxNode(): ISyntaxNode( Token_Type::OPEN_CIRCLE_BRACKET ) {}

    void accept( const std::shared_ptr<ISyntaxNodeVisitor>& visitor ) override;
};

using OpenCircleBracketSyntaxNodeSP = std::shared_ptr<OpenCircleBracketSyntaxNode>;
