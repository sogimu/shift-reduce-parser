#pragma once

#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class E;
class T;
class P;

class SyntaxNodeDiv: public ISyntaxNode
{
public:
    SyntaxNodeDiv(const ISyntaxNodeSP& f0, const ISyntaxNodeSP& f1)
        : ISyntaxNode(Token_Type::DIV)
    {
        Add(f0);
        Add(f1);
    }

};
