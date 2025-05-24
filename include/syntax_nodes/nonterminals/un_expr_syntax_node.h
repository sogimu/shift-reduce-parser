#pragma once

#include "terminals/f_syntax_node.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;

class UnExprSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< UnExprSyntaxNode >

{
public:
  enum class Type
  {
    Negation
  };

   UnExprSyntaxNode();
   UnExprSyntaxNode( const Type& type, const ISyntaxNodeSP& f0 );

   Type type() const;

   // std::vector< FSyntaxNodeSP > Arguments() const;
   // ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child ) override;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
private:
  Type mType;
};

using UnExprSyntaxNodeSP = std::shared_ptr< UnExprSyntaxNode >;
