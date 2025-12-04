#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include "lexical_tokens.h"
#include <memory>

class ISyntaxNodeVisitor;

class MinusSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< MinusSyntaxNode >
{
public:
   MinusSyntaxNode( const MinusSyntaxNode& node );
   MinusSyntaxNode( LexicalTokens::LexicalToken token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   
   bool compare( const ISyntaxNode& node ) const override;
};

using MinusSyntaxNodeSP = std::shared_ptr< MinusSyntaxNode >;
