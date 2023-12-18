#pragma once

#include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "base/f_syntax_node.h"

class ISyntaxNodeVisitor;

class DiffSyntaxNode :
        public ISyntaxNode,
        public std::enable_shared_from_this<DiffSyntaxNode>

{
public:
    DiffSyntaxNode(const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1)
        : ISyntaxNode{Token_Type::DIFF}
    {
        Add(f0);
        Add(f1);
    }

    std::vector<FSyntaxNodeSP> Arguments() const;

    void accept(const std::shared_ptr<ISyntaxNodeVisitor>& visitor) override;
};

using DiffSyntaxNodeSP = std::shared_ptr<DiffSyntaxNode>;
