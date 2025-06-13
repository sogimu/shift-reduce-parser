#pragma once

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

#include "nonterminals/function_statment_syntax_node.h"
#include <memory>

namespace
{
class SyntaxNodeShallowCopyVisitor : public ISyntaxNodeVisitor
{
public:
   ~SyntaxNodeShallowCopyVisitor() = default;

   void visit( const BolSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< BolSyntaxNode >();
   }

   void visit( const EolSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< EolSyntaxNode >();
   }

   void visit( const PlusSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< PlusSyntaxNode >();
   }

   void visit( const MinusSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< MinusSyntaxNode >();
   }

   void visit( const AsteriskSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< AsteriskSyntaxNode >();
   }
   void visit( const SlashSyntaxNodeSP& /* node  */ ) override
   {
      mCopy = std::make_shared< SlashSyntaxNode >();
   }

   void visit( const NumberSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< NumberSyntaxNode >( *node );
   }

   void visit( const FSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FSyntaxNode >( *node );
   }

   void visit( const UnExprSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< UnExprSyntaxNode >( node->type() );
   }
   void visit( const BinExprSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< BinExprSyntaxNode >( node->type() );
   }

   void visit( const SemicolonSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< SemicolonSyntaxNode >();
   }

   void visit( const StatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< StatmentSyntaxNode >();
   }

   void visit( const ScopeSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ScopeSyntaxNode >();
   }

   void visit( const OpenCurlyBracketSyntaxNodeSP& /*  node */ ) override
   {
      mCopy = std::make_shared< OpenCurlyBracketSyntaxNode >();
   }

   void visit( const CloseCurlyBracketSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< CloseCurlyBracketSyntaxNode >();
   }

   void visit( const OpenCircleBracketSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< OpenCircleBracketSyntaxNode >();
   }

   void visit( const CloseCircleBracketSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< CloseCircleBracketSyntaxNode >();
   }

   void visit( const VaribleSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< VaribleSyntaxNode >( node->name() );
   }

   void visit( const PrintStatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< PrintStatmentSyntaxNode >();
   }

   void visit( const VaribleAssigmentStatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< VaribleAssigmentStatmentSyntaxNode >();
   }

   void visit( const NameSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< NameSyntaxNode >( *node );
   }

   void visit( const CommaSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< CommaSyntaxNode >();
   }

   void visit( const PrintSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< PrintSyntaxNode >();
   }

   void visit( const EqualSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< EqualSyntaxNode >();
   }

   void visit( const LessSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< LessSyntaxNode >();
   }

   void visit( const MoreSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< MoreSyntaxNode >();
   }

   void visit( const IfSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< IfSyntaxNode >();
   }

   void visit( const IfStatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< IfStatmentSyntaxNode >();
   }
   void visit( const WhileSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< WhileSyntaxNode >();
   }

   void visit( const WhileStatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< WhileStatmentSyntaxNode >();
   }

   void visit( const FunctionStatmentSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionStatmentSyntaxNode >( node->name() );
   }

   void visit( const FunctionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionSyntaxNode >();
   }

   void visit( const FunctionCallSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionCallSyntaxNode >( node->name() );
   }

   void visit( const ReturnSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ReturnSyntaxNode >();
   }

   void visit( const ReturnStatmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ReturnStatmentSyntaxNode >();
   }

   ISyntaxNodeSP get_copy() const
   {
      return mCopy;
   }

private:
   ISyntaxNodeSP mCopy;
};
using SyntaxNodeShallowCopyVisitorSP = std::shared_ptr< SyntaxNodeShallowCopyVisitor >;
} // namespace

static ISyntaxNodeSP make_shallow_copy( const ISyntaxNodeSP& node )
{
   const auto& visitor = std::make_shared< SyntaxNodeShallowCopyVisitor >();
   node->accept( visitor );
   return visitor->get_copy();
};
