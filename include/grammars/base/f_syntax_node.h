#pragma once

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "base/minus_syntax_node.h"
#include "base/number_syntax_node.h"

class ISyntaxNodeVisitor;

class FSyntaxNode :
    public ISyntaxNode,
    public std::enable_shared_from_this<FSyntaxNode>

{
public:
    FSyntaxNode(const int& number)
        : ISyntaxNode{Token_Type::F}
    {
        mValue = number;
    }

    FSyntaxNode(const MinusSyntaxNodeSP& minus, const NumberSyntaxNodeSP& number)
        : ISyntaxNode{Token_Type::F}
    {
        mValue = -1 * number->value();
    }

    FSyntaxNode(const NumberSyntaxNodeSP& number)
        : ISyntaxNode{Token_Type::F}
    {
        mValue = number->value();
    }

    int value() const
    {
        return mValue;
    }

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;

private:
    int mValue;

};

using FSyntaxNodeSP = std::shared_ptr<FSyntaxNode>;
