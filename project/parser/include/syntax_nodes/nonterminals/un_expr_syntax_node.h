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

   UnExprSyntaxNode( const UnExprSyntaxNode& un_expr_syntax_node );
   UnExprSyntaxNode( const Type& type, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   UnExprSyntaxNode( const Type& type, const ISyntaxNodeSP& argument, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );

   Type type() const;

   // std::vector< FSyntaxNodeSP > Arguments() const;
   // ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child ) override;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
  Type mType;
};

using UnExprSyntaxNodeSP = std::shared_ptr< UnExprSyntaxNode >;
