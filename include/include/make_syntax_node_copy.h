#pragma once

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"

#include <memory>

namespace
{
class SyntaxNodeCopyVisitor : public ISyntaxNodeVisitor
{
public:
   ~SyntaxNodeCopyVisitor() = default;

   void visit( const BolSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< BolSyntaxNode >( *node );
   }

   void visit( const EolSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< EolSyntaxNode >( *node );
   }

   void visit( const PlusSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< PlusSyntaxNode >( *node );
   }

   void visit( const MinusSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< MinusSyntaxNode >( *node );
   }

   void visit( const AsteriskSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< AsteriskSyntaxNode >( *node );
   }
   void visit( const SlashSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< SlashSyntaxNode >( *node );
   }

   void visit( const NumberSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< NumberSyntaxNode >( *node );
   }

   void visit( const FSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FSyntaxNode >( *node );
   }

   void visit( const AdditionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< AdditionSyntaxNode >( *node );
   }

   void visit( const SubtractionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< SubtractionSyntaxNode >( *node );
   }
   void visit( const MultiplySyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< MultiplySyntaxNode >( *node );
   }
   void visit( const DivisionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< DivisionSyntaxNode >( *node );
   }

   void visit( const SemicolonSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< SemicolonSyntaxNode >( *node );
   }

   void visit( const ExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ExpressionSyntaxNode >( *node );
   }

   void visit( const ScopeSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ScopeSyntaxNode >( *node );
   }

   void visit( const OpenCurlyBracketSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< OpenCurlyBracketSyntaxNode >( *node );
   }

   void visit( const CloseCurlyBracketSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< CloseCurlyBracketSyntaxNode >( *node );
   }

   void visit( const OpenCircleBracketSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< OpenCircleBracketSyntaxNode >( *node );
   }

   void visit( const CloseCircleBracketSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< CloseCircleBracketSyntaxNode >( *node );
   }

   void visit( const ComputationalExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ComputationalExpressionSyntaxNode >( *node );
   }

   void visit( const VaribleSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< VaribleSyntaxNode >( *node );
   }

   void visit( const ConditionalExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ConditionalExpressionSyntaxNode >( *node );
   }

   void visit( const PrintExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< PrintExpressionSyntaxNode >( *node );
   }

   void visit( const VaribleAssigmentSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< VaribleAssigmentSyntaxNode >( *node );
   }

   void visit( const NameSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< NameSyntaxNode >( *node );
   }

   void visit( const CommaSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< CommaSyntaxNode >( *node );
   }

   void visit( const PrintSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< PrintSyntaxNode >( *node );
   }

   void visit( const EqualSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< EqualSyntaxNode >( *node );
   }

   void visit( const LessSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< LessSyntaxNode >( *node );
   }

   void visit( const MoreSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< MoreSyntaxNode >( *node );
   }

   void visit( const IfSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< IfSyntaxNode >( *node );
   }

   void visit( const IfExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< IfExpressionSyntaxNode >( *node );
   }
   void visit( const WhileSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< WhileSyntaxNode >( *node );
   }

   void visit( const WhileExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< WhileExpressionSyntaxNode >( *node );
   }

   void visit( const FunctionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionSyntaxNode >( *node );
   }

   void visit( const FunctionCallSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< FunctionCallSyntaxNode >( *node );
   }

   void visit( const ReturnSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ReturnSyntaxNode >( *node );
   }

   void visit( const ReturnExpressionSyntaxNodeSP& node ) override
   {
      mCopy = std::make_shared< ReturnExpressionSyntaxNode >( *node );
   }

   ISyntaxNodeSP get_copy() const
   {
      return mCopy;
   }

private:
   ISyntaxNodeSP mCopy;
};
using SyntaxNodeCopyVisitorSP = std::shared_ptr< SyntaxNodeCopyVisitor >;
} // namespace

static ISyntaxNodeSP make_copy( const ISyntaxNodeSP& node )
{
   const auto& visitor = std::make_shared< SyntaxNodeCopyVisitor >();
   node->accept( visitor );
   return visitor->get_copy();
};
