#pragma once

#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class WrappedSyntaxNode : public ISyntaxNode
{
public:
    WrappedSyntaxNode(const Token_Type& token_type, const ISyntaxNodeSP& node)
        : ISyntaxNode( token_type )
        , mNode{ node }
    {
    }

    void Add(const ISyntaxNodeSP& child) override
    {
        mNode->Add(child);
    }

    ISyntaxNodeSP operator[](size_t index) const override
    {
        return mNode->operator[](index);
    }

private:
    ISyntaxNodeSP mNode;
};
