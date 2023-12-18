#pragma once

#include <vector>
#include <string>
#include "enums.h"
#include "i_syntax_node.h"
//#include "expression_syntax_node.h"

class ISyntaxNodeVisitor;

class ScopeSyntaxNode :
    public ISyntaxNode,
    public std::enable_shared_from_this<ScopeSyntaxNode>

{
public:
    ScopeSyntaxNode() = default;
    ScopeSyntaxNode(const ISyntaxNodeSP& expression)
        : ISyntaxNode{Token_Type::SCOPE_EXPRESSION}
    {
        Add(expression);
    }

    ScopeSyntaxNode(const std::vector<ISyntaxNodeSP>& expressions)
        : ISyntaxNode{Token_Type::SCOPE_EXPRESSION}
    {
        for( const auto& expression : expressions )
            Add(expression);
    }
    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;
};

using ScopeSyntaxNodeSP = std::shared_ptr<ScopeSyntaxNode>;
