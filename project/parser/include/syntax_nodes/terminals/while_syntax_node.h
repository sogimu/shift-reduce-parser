#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class WhileSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< WhileSyntaxNode >
{
public:
   WhileSyntaxNode( const WhileSyntaxNode& node );
   WhileSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using WhileSyntaxNodeSP = std::shared_ptr< WhileSyntaxNode >;
