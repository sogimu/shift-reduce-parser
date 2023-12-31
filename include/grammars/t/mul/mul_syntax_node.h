#pragma once

#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class E;
class T;
class P;

class SyntaxNodeMul : public ISyntaxNode
{
public:
    SyntaxNodeMul(const ISyntaxNodeSP& f0, const ISyntaxNodeSP& f1)
        : ISyntaxNode(Token_Type::MUL)
    {
        Add(f0);
        Add(f1);
    }

};
