#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"

class ISyntaxNodeVisitor;

class StatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< StatmentSyntaxNode >
{
public:
   StatmentSyntaxNode( const ISyntaxNodeSP& syntax_node, const LexicalTokens::LexicalToken& semicolon_lexical_token );
   StatmentSyntaxNode( const ISyntaxNodeSP& syntax_node );
   
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
   
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
   void add_lexical_token(const LexicalTokens::LexicalToken& token);

private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};

using StatmentSyntaxNodeSP = std::shared_ptr< StatmentSyntaxNode >;
