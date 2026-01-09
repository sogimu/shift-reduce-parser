#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class VarSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< VarSyntaxNode >
{
public:
   VarSyntaxNode( const VarSyntaxNode& node );
   VarSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using VarSyntaxNodeSP = std::shared_ptr< VarSyntaxNode >;
