#pragma once

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

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

   void visit( const AdditionSyntaxNodeSP& /*  node */ ) override
   {
      mCopy = std::make_shared< AdditionSyntaxNode >();
   }

   void visit( const SubtractionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< SubtractionSyntaxNode >();
   }
   void visit( const MultiplySyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< MultiplySyntaxNode >();
   }
   void visit( const DivisionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< DivisionSyntaxNode >();
   }

   void visit( const SemicolonSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< SemicolonSyntaxNode >();
   }

   void visit( const ExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ExpressionSyntaxNode >();
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

   void visit( const ComputationalExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ComputationalExpressionSyntaxNode >();
   }

   void visit( const VaribleSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< VaribleSyntaxNode >( node->name() );
   }

   void visit( const ConditionalExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ConditionalExpressionSyntaxNode >( node->type() );
   }

   void visit( const PrintExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< PrintExpressionSyntaxNode >();
   }

   void visit( const VaribleAssigmentSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< VaribleAssigmentSyntaxNode >();
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

   void visit( const IfExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< IfExpressionSyntaxNode >();
   }
   void visit( const WhileSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< WhileSyntaxNode >();
   }

   void visit( const WhileExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< WhileExpressionSyntaxNode >();
   }

   void visit( const FunctionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionSyntaxNode >( node->name() );
   }

   void visit( const FunctionCallSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionCallSyntaxNode >( node->name() );
   }

   void visit( const ReturnSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ReturnSyntaxNode >();
   }

   void visit( const ReturnExpressionSyntaxNodeSP& /* node */ ) override
   {
      mCopy = std::make_shared< ReturnExpressionSyntaxNode >();
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
