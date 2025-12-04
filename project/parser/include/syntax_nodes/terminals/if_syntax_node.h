#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class IfSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< IfSyntaxNode >
{
public:
   IfSyntaxNode( const IfSyntaxNode& node );
   IfSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using IfSyntaxNodeSP = std::shared_ptr< IfSyntaxNode >;
