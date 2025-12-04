#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class PlusSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< PlusSyntaxNode >
{
public:
   PlusSyntaxNode( const PlusSyntaxNode& node );
   
   PlusSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   
   bool compare( const ISyntaxNode& node ) const override;
};

using PlusSyntaxNodeSP = std::shared_ptr< PlusSyntaxNode >;
