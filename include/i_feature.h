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

class IFeature
{
public:
    virtual bool IsFit(const Token_Type&) const = 0;
    virtual ~IFeature() {};
};
using IFeatureSP = std::shared_ptr<IFeature>;
