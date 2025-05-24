#pragma once

#include <memory>
#include "terminals/bol_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/eol_syntax_node.h"
#include "terminals/equal_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/if_syntax_node.h"
#include "terminals/while_syntax_node.h"
#include "terminals/less_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/more_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/number_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/open_curly_bracket_syntax_node.h"
#include "terminals/plus_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/print_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "terminals/slash_syntax_node.h"
#include "terminals/return_syntax_node.h"
#include "terminals/function_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor
{
public:
   virtual ~ISyntaxNodeVisitor() = default;
   virtual void visit( const BolSyntaxNodeSP& ) = 0;
   virtual void visit( const EolSyntaxNodeSP& ) = 0;
   virtual void visit( const PlusSyntaxNodeSP& ) = 0;
   virtual void visit( const MinusSyntaxNodeSP& ) = 0;
   virtual void visit( const AsteriskSyntaxNodeSP& ) = 0;
   virtual void visit( const SlashSyntaxNodeSP& ) = 0;
   virtual void visit( const NumberSyntaxNodeSP& ) = 0;
   virtual void visit( const FSyntaxNodeSP& ) = 0;
   virtual void visit( const UnExprSyntaxNodeSP& ) = 0;
   virtual void visit( const BinExprSyntaxNodeSP& ) = 0;
   virtual void visit( const SemicolonSyntaxNodeSP& ) = 0;
   virtual void visit( const StatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const ScopeSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const ComputationalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const VaribleSyntaxNodeSP& ) = 0;
   virtual void visit( const ConditionalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintStatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintSyntaxNodeSP& ) = 0;
   virtual void visit( const EqualSyntaxNodeSP& ) = 0;
   virtual void visit( const LessSyntaxNodeSP& ) = 0;
   virtual void visit( const MoreSyntaxNodeSP& ) = 0;
   virtual void visit( const IfSyntaxNodeSP& ) = 0;
   virtual void visit( const IfStatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const WhileSyntaxNodeSP& ) = 0;
   virtual void visit( const WhileStatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionStatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionCallSyntaxNodeSP& ) = 0;
   virtual void visit( const VaribleAssigmentStatmentSyntaxNodeSP& ) = 0;
   virtual void visit( const NameSyntaxNodeSP& ) = 0;
   virtual void visit( const CommaSyntaxNodeSP& ) = 0;
   virtual void visit( const ReturnSyntaxNodeSP& ) = 0;
   virtual void visit( const ReturnStatmentSyntaxNodeSP& ) = 0;
};
using ISyntaxNodeVisitorSP = std::shared_ptr< ISyntaxNodeVisitor >;
