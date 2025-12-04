#pragma once

#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class AsteriskSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< AsteriskSyntaxNode >
{
public:
   AsteriskSyntaxNode( const AsteriskSyntaxNode& node );
   AsteriskSyntaxNode( const LexicalTokens::LexicalToken& token );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const;
};

using AsteriskSyntaxNodeSP = std::shared_ptr< AsteriskSyntaxNode >;
