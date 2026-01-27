#pragma once

#include "lexical_tokens.h"
#include <string>

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class VaribleAssigmentStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< VaribleAssigmentStatmentSyntaxNode >
{
public:
   enum class Context
   {
      GLOBAL,
      LOCAL
   };
   VaribleAssigmentStatmentSyntaxNode( const VaribleAssigmentStatmentSyntaxNode& node );
   VaribleAssigmentStatmentSyntaxNode( const NameSyntaxNodeSP& name, const ISyntaxNodeSP& node, LexicalTokens::LexicalToken token, Context context = Context::GLOBAL );
   VaribleAssigmentStatmentSyntaxNode( const NameSyntaxNodeSP& target_name, const NameSyntaxNodeSP& source_name, LexicalTokens::LexicalToken token, Context context = Context::GLOBAL );
   VaribleAssigmentStatmentSyntaxNode( const ISyntaxNodeSP& target, const ISyntaxNodeSP& node, LexicalTokens::LexicalToken token, Context context = Context::GLOBAL );

   std::string name() const;
   ISyntaxNodeSP source() const;
   NameSyntaxNodeSP target() const;
   Context context() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
   void add_lexical_token(const LexicalTokens::LexicalToken& token);

private:
    Context mContext = Context::GLOBAL;
    std::vector< LexicalTokens::LexicalToken > mTokens;
};

using VaribleAssigmentStatmentSyntaxNodeSP = std::shared_ptr< VaribleAssigmentStatmentSyntaxNode >;
