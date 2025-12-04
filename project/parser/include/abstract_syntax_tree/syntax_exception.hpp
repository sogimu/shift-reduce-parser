#pragma once

#include <exception>
#include <stdexcept>
#include <deque>
#include "i_syntax_node.h"

class SyntaxException : public std::runtime_error
{
using Stack = std::deque< ISyntaxNodeSP >;
public:
    SyntaxException(const std::string& msg, const Stack& stack) 
        : std::runtime_error{ msg }
        , mStack{ stack }
    {
    }
    
    Stack stack() const
    {
        return mStack;
    }

private:
    Stack mStack;
};
