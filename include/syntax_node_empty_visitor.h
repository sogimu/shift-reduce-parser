#pragma once

#include "i_syntax_node_visitor.h"

#include "nonterminals/function_statment_syntax_node.h"
#include <functional>
#include <memory>

class SyntaxNodeEmptyVisitor : public ISyntaxNodeVisitor
{
public:
   struct Handlers
   {
      std::function< void( const ISyntaxNodeSP& ) > default_handler = []( const ISyntaxNodeSP& ) {};
      std::function< void( const BolSyntaxNodeSP& ) > bol_syntax_node = [ this ]( const BolSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const PlusSyntaxNodeSP& ) > plus_syntax_node = [ this ]( const PlusSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const MinusSyntaxNodeSP& ) > minus_syntax_node = [ this ]( const MinusSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const AsteriskSyntaxNodeSP& ) > asterisk_syntax_node = [ this ]( const AsteriskSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const SlashSyntaxNodeSP& ) > slash_syntax_node = [ this ]( const SlashSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const NumberSyntaxNodeSP& ) > number_syntax_node = [ this ]( const NumberSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const FSyntaxNodeSP& ) > f_syntax_node = [ this ]( const FSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const UnExprSyntaxNodeSP& ) > un_expr_syntax_node = [ this ]( const UnExprSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const BinExprSyntaxNodeSP& ) > bin_expr_syntax_node = [ this ]( const BinExprSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const EolSyntaxNodeSP& ) > eol_syntax_node = [ this ]( const EolSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const SemicolonSyntaxNodeSP& ) > semicolon_syntax_node = [ this ]( const SemicolonSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const StatmentSyntaxNodeSP& ) > statment_syntax_node = [ this ]( const StatmentSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const ScopeSyntaxNodeSP& ) > scope_statment_syntax_node = [ this ]( const ScopeSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const OpenCurlyBracketSyntaxNodeSP& ) > open_curly_bracket_syntax_node = [ this ]( const OpenCurlyBracketSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const CloseCurlyBracketSyntaxNodeSP& ) > close_curly_bracket_syntax_node = [ this ]( const CloseCurlyBracketSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const OpenCircleBracketSyntaxNodeSP& ) > open_circle_bracket_syntax_node = [ this ]( const OpenCircleBracketSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const CloseCircleBracketSyntaxNodeSP& ) > close_circle_bracket_syntax_node = [ this ]( const CloseCircleBracketSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const ComputationalExpressionSyntaxNodeSP& ) > computational_expression_syntax_node =
         [ this ]( const ComputationalExpressionSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const VaribleSyntaxNodeSP& ) > varible_syntax_node = [ this ]( const VaribleSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const ConditionalExpressionSyntaxNodeSP& ) > conditional_expression_syntax_node = [ this ]( const ConditionalExpressionSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const PrintStatmentSyntaxNodeSP& ) > print_statment_syntax_node = [ this ]( const PrintStatmentSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const VaribleAssigmentStatmentSyntaxNodeSP& ) > varible_assigment_statment_syntax_node =
         [ this ]( const VaribleAssigmentStatmentSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const NameSyntaxNodeSP& ) > name_syntax_node = [ this ]( const NameSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const CommaSyntaxNodeSP& ) > comma_syntax_node = [ this ]( const CommaSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const PrintSyntaxNodeSP& ) > print_syntax_node = [ this ]( const PrintSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const EqualSyntaxNodeSP& ) > equal_syntax_node = [ this ]( const EqualSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const LessSyntaxNodeSP& ) > less_syntax_node = [ this ]( const LessSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const MoreSyntaxNodeSP& ) > more_syntax_node = [ this ]( const MoreSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const IfSyntaxNodeSP& ) > if_syntax_node = [ this ]( const IfSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const IfStatmentSyntaxNodeSP& ) > if_statment_syntax_node = [ this ]( const IfStatmentSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const WhileSyntaxNodeSP& ) > while_syntax_node = [ this ]( const WhileSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const WhileStatmentSyntaxNodeSP& ) > while_statment_syntax_node = [ this ]( const WhileStatmentSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const FunctionStatmentSyntaxNodeSP& ) > function_statment_syntax_node = [ this ]( const FunctionStatmentSyntaxNodeSP& node )
      { default_handler( node ); };
      std::function< void( const FunctionCallSyntaxNodeSP& ) > function_call_syntax_node = [ this ]( const FunctionCallSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const ReturnSyntaxNodeSP& ) > return_syntax_node = [ this ]( const ReturnSyntaxNodeSP& node ) { default_handler( node ); };
      std::function< void( const ReturnStatmentSyntaxNodeSP& ) > return_statment_syntax_node = [ this ]( const ReturnStatmentSyntaxNodeSP& node )
      { default_handler( node ); };
   };

   SyntaxNodeEmptyVisitor( const Handlers& handlers )
      : mHandlers{ handlers }
   {
   }

   ~SyntaxNodeEmptyVisitor() = default;

   void visit( const BolSyntaxNodeSP& node ) override
   {
      mHandlers.bol_syntax_node( node );
   }

   void visit( const EolSyntaxNodeSP& node ) override
   {
      mHandlers.eol_syntax_node( node );
   }

   void visit( const PlusSyntaxNodeSP& node ) override
   {
      mHandlers.plus_syntax_node( node );
   }

   void visit( const MinusSyntaxNodeSP& node ) override
   {
      mHandlers.minus_syntax_node( node );
   }

   void visit( const AsteriskSyntaxNodeSP& node ) override
   {
      mHandlers.asterisk_syntax_node( node );
   }
   void visit( const SlashSyntaxNodeSP& node ) override
   {
      mHandlers.slash_syntax_node( node );
   }

   void visit( const NumberSyntaxNodeSP& node ) override
   {
      mHandlers.number_syntax_node( node );
   }

   void visit( const FSyntaxNodeSP& node ) override
   {
      mHandlers.f_syntax_node( node );
   }

   void visit( const UnExprSyntaxNodeSP& node ) override
   {
      mHandlers.un_expr_syntax_node( node );
   }
   void visit( const BinExprSyntaxNodeSP& node ) override
   {
      mHandlers.bin_expr_syntax_node( node );
   }
   void visit( const SemicolonSyntaxNodeSP& node ) override
   {
      mHandlers.semicolon_syntax_node( node );
   }

   void visit( const StatmentSyntaxNodeSP& node ) override
   {
      mHandlers.statment_syntax_node( node );
   }

   void visit( const ScopeSyntaxNodeSP& node ) override
   {
      mHandlers.scope_statment_syntax_node( node );
   }

   void visit( const OpenCurlyBracketSyntaxNodeSP& node ) override
   {
      mHandlers.open_curly_bracket_syntax_node( node );
   }

   void visit( const CloseCurlyBracketSyntaxNodeSP& node ) override
   {
      mHandlers.close_curly_bracket_syntax_node( node );
   }

   void visit( const OpenCircleBracketSyntaxNodeSP& node ) override
   {
      mHandlers.open_circle_bracket_syntax_node( node );
   }

   void visit( const CloseCircleBracketSyntaxNodeSP& node ) override
   {
      mHandlers.close_circle_bracket_syntax_node( node );
   }

   void visit( const ComputationalExpressionSyntaxNodeSP& node ) override
   {
      mHandlers.computational_expression_syntax_node( node );
   }

   void visit( const VaribleSyntaxNodeSP& node ) override
   {
      mHandlers.varible_syntax_node( node );
   }

   void visit( const ConditionalExpressionSyntaxNodeSP& node ) override
   {
      mHandlers.conditional_expression_syntax_node( node );
   }

   void visit( const PrintStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.print_statment_syntax_node( node );
   }

   void visit( const VaribleAssigmentStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.varible_assigment_statment_syntax_node( node );
   }

   void visit( const NameSyntaxNodeSP& node ) override
   {
      mHandlers.name_syntax_node( node );
   }

   void visit( const CommaSyntaxNodeSP& node ) override
   {
      mHandlers.comma_syntax_node( node );
   }

   void visit( const PrintSyntaxNodeSP& node ) override
   {
      mHandlers.print_syntax_node( node );
   }

   void visit( const EqualSyntaxNodeSP& node ) override
   {
      mHandlers.equal_syntax_node( node );
   }

   void visit( const LessSyntaxNodeSP& node ) override
   {
      mHandlers.less_syntax_node( node );
   }

   void visit( const MoreSyntaxNodeSP& node ) override
   {
      mHandlers.more_syntax_node( node );
   }

   void visit( const IfSyntaxNodeSP& node ) override
   {
      mHandlers.if_syntax_node( node );
   }

   void visit( const IfStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.if_statment_syntax_node( node );
   }
   void visit( const WhileSyntaxNodeSP& node ) override
   {
      mHandlers.while_syntax_node( node );
   }

   void visit( const WhileStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.while_statment_syntax_node( node );
   }

   void visit( const FunctionStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.function_statment_syntax_node( node );
   }

   void visit( const FunctionCallSyntaxNodeSP& node ) override
   {
      mHandlers.function_call_syntax_node( node );
   }

   void visit( const ReturnSyntaxNodeSP& node ) override
   {
      mHandlers.return_syntax_node( node );
   }

   void visit( const ReturnStatmentSyntaxNodeSP& node ) override
   {
      mHandlers.return_statment_syntax_node( node );
   }

private:
   Handlers mHandlers;
};
using SyntaxNodeEmptyVisitorSP = std::shared_ptr< SyntaxNodeEmptyVisitor >;
