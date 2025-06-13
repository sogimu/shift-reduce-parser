#pragma once

#include <string>

using namespace std;

class NaiveStackInterpreter
{
public:
   double eval( const std::string& expression ) const;
};
