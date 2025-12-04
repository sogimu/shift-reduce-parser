#pragma once

#include <string>

#include "i_syntax_node.h"
#include "i_terminal_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode : public ITerminalSyntaxNode, public std::enable_shared_from_this< NameSyntaxNode >
{
public:
   NameSyntaxNode( const NameSyntaxNode& node );
   
   NameSyntaxNode( const LexicalTokens::LexicalToken& token );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   
   bool compare( const ISyntaxNode& node ) const override;

   std::string value() const;

private:
   std::string mValue;
};

using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;
