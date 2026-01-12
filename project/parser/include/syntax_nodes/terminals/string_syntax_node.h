#pragma once

#include <string>

#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

class ISyntaxNodeVisitor;

class StringSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< StringSyntaxNode >
{
public:
   StringSyntaxNode( const StringSyntaxNode& node );
   
   StringSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   
   bool compare( const ISyntaxNode& node ) const override;

   std::string value() const;

private:
   std::string mValue;
};

using StringSyntaxNodeSP = std::shared_ptr< StringSyntaxNode >;
