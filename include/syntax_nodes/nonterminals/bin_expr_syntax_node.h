#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>

class BinExprSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< BinExprSyntaxNode >
{
public:
  enum class Type
  {
    Addition,
    Substruction,
    Multiply,
    Division,
    Equal,
    Less,
    LessEqual,
    More,
    MoreEqual
  };
   BinExprSyntaxNode();
   BinExprSyntaxNode( const Type& type, const ISyntaxNodeSP& f0, const ISyntaxNodeSP& f1 );
   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   // ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child ) override;

   Type type() const;

private:
  Type mType;
};

using BinExprSyntaxNodeSP = std::shared_ptr< BinExprSyntaxNode >;
using BinExprSyntaxNodeCSP = std::shared_ptr< const BinExprSyntaxNode >;
