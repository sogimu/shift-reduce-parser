#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"
#include "lexical_tokens.h"

#include <memory>

class ISyntaxNodeVisitor;

class BolSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< BolSyntaxNode >
{
public:
   BolSyntaxNode( const BolSyntaxNode& node );
   BolSyntaxNode( LexicalTokens::LexicalToken token );
   
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using BolSyntaxNodeSP = std::shared_ptr< BolSyntaxNode >;
