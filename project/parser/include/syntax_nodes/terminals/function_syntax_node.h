#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class FunctionSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< FunctionSyntaxNode >
{
public:
   FunctionSyntaxNode( const FunctionSyntaxNode& node );
   FunctionSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using FunctionSyntaxNodeSP = std::shared_ptr< FunctionSyntaxNode >;
