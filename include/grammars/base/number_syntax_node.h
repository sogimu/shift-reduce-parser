#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class NumberSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< NumberSyntaxNode >
{
public:
   NumberSyntaxNode( const std::string& text )
      : ISyntaxNode{ Token_Type::INT }
   {
      mValue = std::stod( text );
   }

   int value() const
   {
      return mValue;
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

private:
   int mValue;
};

using NumberSyntaxNodeSP = std::shared_ptr< NumberSyntaxNode >;
using NumberSyntaxNodeCSP = std::shared_ptr< const NumberSyntaxNode >;
