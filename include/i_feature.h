#pragma once

#include "lexical_tokens.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <vector>

class IFeature
{
public:
   virtual bool IsFit( const Token_Type& ) const = 0;
   virtual ~IFeature(){};
};
using IFeatureSP = std::shared_ptr< IFeature >;
