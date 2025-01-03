#pragma once

#include <string>

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class VaribleAssigmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< VaribleAssigmentSyntaxNode >
{
public:
   enum class Context
   {
      GLOBAL,
      LOCAL
   };
   VaribleAssigmentSyntaxNode( Context context = Context::GLOBAL );
   VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& name, const ComputationalExpressionSyntaxNodeSP& node, Context context = Context::GLOBAL );
   VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& target_name, const NameSyntaxNodeSP& source_name, Context context = Context::GLOBAL );

   std::string name() const;
   ComputationalExpressionSyntaxNodeSP source() const;
   NameSyntaxNodeSP target() const;
   Context context() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

private:
   Context mContext = Context::GLOBAL;
};

using VaribleAssigmentSyntaxNodeSP = std::shared_ptr< VaribleAssigmentSyntaxNode >;
