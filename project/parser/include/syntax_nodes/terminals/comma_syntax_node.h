#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class CommaSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< CommaSyntaxNode >
{
public:
   CommaSyntaxNode( const CommaSyntaxNode& node );
   CommaSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using CommaSyntaxNodeSP = std::shared_ptr< CommaSyntaxNode >;
