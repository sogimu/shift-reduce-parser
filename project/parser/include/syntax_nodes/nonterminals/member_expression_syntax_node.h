#pragma once

#include "enums.h"
#include "i_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"

#include <variant>
#include <vector>

class ISyntaxNodeVisitor;

class MemberExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< MemberExpressionSyntaxNode >

{
public:
   MemberExpressionSyntaxNode( const MemberExpressionSyntaxNode& member_expression );
   MemberExpressionSyntaxNode( const ISyntaxNodeSP& target, const ISyntaxNodeSP& key_or_index_node, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
   const std::string container_varible_name() const;
   const std::variant<size_t, std::string>& key_or_index() const;
private:
   std::vector< LexicalTokens::LexicalToken > mTokens;
   std::string mContainerVaribleName;
   std::variant<size_t, std::string> mKeyOrIndex;
};

using MemberExpressionSyntaxNodeSP = std::shared_ptr< MemberExpressionSyntaxNode >;
