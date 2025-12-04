#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include "lexical_tokens.h"
#include <string>

class ISyntaxNodeVisitor;

class ITerminalSyntaxNode : public ISyntaxNode
{
public:
   ITerminalSyntaxNode( Token_Type token_type, const std::vector< LexicalTokens::LexicalToken >& tokens )
      : ISyntaxNode{ token_type }
      , mTokens{ tokens }
   {
   }

   ITerminalSyntaxNode( Token_Type token_type, const LexicalTokens::LexicalToken& token )
      : ISyntaxNode{ token_type }
      , mTokens{ token }
   {
   }
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override { return { mTokens }; };
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};
