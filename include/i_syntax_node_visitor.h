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
#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/subtraction/subtraction_syntax_node.h"
#include "nonterminals/addition/addition_syntax_node.h"
#include "nonterminals/multiply/multiply_syntax_node.h"
#include "nonterminals/division/division_syntax_node.h"
#include "nonterminals/expression_syntax_node.h"
#include "nonterminals/if_expression_syntax_node.h"
#include "nonterminals/while_expression_syntax_node.h"
#include "nonterminals/function_call_or_definition_syntax_node.h"
#include "nonterminals/function_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/print_expression_syntax_node.h"
#include "nonterminals/scope_syntax_node.h"
#include "nonterminals/varible_assigment_syntax_node.h"
#include "nonterminals/return_expression_syntax_node.h"
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
   virtual void visit( const AdditionSyntaxNodeSP& ) = 0;
   virtual void visit( const SubtractionSyntaxNodeSP& ) = 0;
   virtual void visit( const MultiplySyntaxNodeSP& ) = 0;
   virtual void visit( const DivisionSyntaxNodeSP& ) = 0;
   virtual void visit( const SemicolonSyntaxNodeSP& ) = 0;
   virtual void visit( const ExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const ScopeSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const ComputationalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const VaribleSyntaxNodeSP& ) = 0;
   virtual void visit( const ConditionalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintSyntaxNodeSP& ) = 0;
   virtual void visit( const EqualSyntaxNodeSP& ) = 0;
   virtual void visit( const LessSyntaxNodeSP& ) = 0;
   virtual void visit( const MoreSyntaxNodeSP& ) = 0;
   virtual void visit( const IfSyntaxNodeSP& ) = 0;
   virtual void visit( const IfExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const WhileSyntaxNodeSP& ) = 0;
   virtual void visit( const WhileExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionCallOrDefinitionSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionSyntaxNodeSP& ) = 0;
   virtual void visit( const FunctionCallSyntaxNodeSP& ) = 0;
   virtual void visit( const VaribleAssigmentSyntaxNodeSP& ) = 0;
   virtual void visit( const NameSyntaxNodeSP& ) = 0;
   virtual void visit( const CommaSyntaxNodeSP& ) = 0;
   virtual void visit( const ReturnSyntaxNodeSP& ) = 0;
   virtual void visit( const ReturnExpressionSyntaxNodeSP& ) = 0;
};
using ISyntaxNodeVisitorSP = std::shared_ptr< ISyntaxNodeVisitor >;
