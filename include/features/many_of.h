#pragma once

#include "enums.h"
#include "i_feature.h"

#include <vector>

class One : public IFeature
{
public:
   One( Token_Type type )
      : mType{ type }
   {
   }

   bool IsFit( const Token_Type& type ) const override
   {
      return mType == type;
   }

private:
   Token_Type mType;
};

static IFeatureSP one( Token_Type type )
{
   return std::make_shared< One >( type );
}

class ManyOf : public IFeature
{
public:
   ManyOf( Token_Type type )
      : mType{ type }
   {
   }

   bool IsFit( const Token_Type& type ) const override
   {
      return mType == type;
   }

private:
   Token_Type mType;
};

static IFeatureSP manyOf( Token_Type type )
{
   return std::make_shared< ManyOf >( type );
}
