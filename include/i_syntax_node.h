#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <stack>
#include <map>
#include <iomanip>
#include <functional>
#include <optional>

#include "lexical_tokens.h"
#include "i_feature.h"

class ISyntaxNodeVisitor;

struct ISyntaxNode;
using ISyntaxNodeSP = std::shared_ptr<ISyntaxNode>;

struct ISyntaxNode
{
    ISyntaxNode() = default;

    ISyntaxNode(const Token_Type& type)
        : mType{ type }
    {
    }

    virtual ~ISyntaxNode()
    {
    };

    virtual void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) = 0;

    const std::string& text() const
    {
        return mText;
    }

    virtual void Add(const ISyntaxNodeSP& child)
    {
        mChildren.emplace_back(child);
    }

    virtual ISyntaxNodeSP operator[](size_t index) const
    {
        if( index >= mChildren.size() )
            return {};
        return mChildren.at(index);
    }

    virtual ISyntaxNodeSP operator[](size_t index)
    {
        if( index >= mChildren.size() )
            return {};
        return mChildren.at(index);
    }

    auto Children() const
    {
        return mChildren;
    }

    auto begin()
    {
        return mChildren.begin();
    }

    auto begin() const
    {
        return mChildren.begin();
    }

    auto end()
    {
        return mChildren.end();
    }

    auto end() const
    {
        return mChildren.end();
    }

private:
    Token_Type mType;
    std::string mText;
    std::vector<ISyntaxNodeSP> mChildren;
};
