#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class ElseSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< ElseSyntaxNode >
{
public:
   ElseSyntaxNode( const ElseSyntaxNode& node );
   ElseSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using ElseSyntaxNodeSP = std::shared_ptr< ElseSyntaxNode >;
