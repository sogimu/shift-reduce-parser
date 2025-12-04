#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class MoreSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< MoreSyntaxNode >
{
public:
   MoreSyntaxNode( const MoreSyntaxNode& node );
   
   MoreSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   
   bool compare( const ISyntaxNode& node ) const override;
};

using MoreSyntaxNodeSP = std::shared_ptr< MoreSyntaxNode >;

