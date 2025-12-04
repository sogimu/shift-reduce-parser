#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include "lexical_tokens.h"

class ISyntaxNodeVisitor;

class EolSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< EolSyntaxNode >
{
public:
   EolSyntaxNode( const EolSyntaxNode& node );
   EolSyntaxNode( LexicalTokens::LexicalToken token );
   
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using EolSyntaxNodeSP = std::shared_ptr< EolSyntaxNode >;
