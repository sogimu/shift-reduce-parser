#pragma once

#include <memory>

class IFeature
{
public:
   virtual bool IsFit( const Token_Type& ) const = 0;
   virtual ~IFeature(){};
};
using IFeatureSP = std::shared_ptr< IFeature >;
