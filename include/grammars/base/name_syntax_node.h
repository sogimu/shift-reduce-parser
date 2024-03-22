#pragma once

// #include <vector>
#include <string>

// #include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< NameSyntaxNode >
{
public:
   NameSyntaxNode( const std::string& value );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;

   std::string value() const;

private:
   std::string mValue;
};

using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;
using NameSyntaxNodeCSP = std::shared_ptr< const NameSyntaxNode >;
