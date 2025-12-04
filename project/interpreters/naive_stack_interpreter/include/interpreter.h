#pragma once

#include <string>
#include "syntax_exception.hpp"

using namespace std;

class Interpreter
{
public:
   double eval( const std::string& expression ) const;
};
