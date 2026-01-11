#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include "lexical_tokens.h"
#include <string>

class ISyntaxNodeVisitor;

class NumberSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< NumberSyntaxNode >
{
public:
   NumberSyntaxNode( const NumberSyntaxNode& node );

   NumberSyntaxNode( const LexicalTokens::LexicalToken& token );

   double value() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
private:
   double mValue;
};

using NumberSyntaxNodeSP = std::shared_ptr< NumberSyntaxNode >;
