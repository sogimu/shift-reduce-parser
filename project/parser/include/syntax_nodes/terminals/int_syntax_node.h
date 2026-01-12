#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include "lexical_tokens.h"
#include <string>

class ISyntaxNodeVisitor;

class IntSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< IntSyntaxNode >
{
public:
   IntSyntaxNode( const IntSyntaxNode& node );

   IntSyntaxNode( const LexicalTokens::LexicalToken& token );

   int value() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
private:
   int mValue;
};

using IntSyntaxNodeSP = std::shared_ptr< IntSyntaxNode >;
