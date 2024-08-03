#pragma once

#include <memory>
#include "base/bol_syntax_node.h"
#include "base/close_circle_bracket_syntax_node.h"
#include "base/close_curly_bracket_syntax_node.h"
#include "base/eol_syntax_node.h"
#include "base/equal_syntax_node.h"
#include "base/f_syntax_node.h"
#include "base/if_syntax_node.h"
#include "base/less_syntax_node.h"
#include "base/minus_syntax_node.h"
#include "base/more_syntax_node.h"
#include "base/name_syntax_node.h"
#include "base/number_syntax_node.h"
#include "base/open_circle_bracket_syntax_node.h"
#include "base/open_curly_bracket_syntax_node.h"
#include "base/plus_syntax_node.h"
#include "base/minus_syntax_node.h"
#include "base/asterisk_syntax_node.h"
#include "base/print_syntax_node.h"
#include "base/semicolon_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "conditional_expression_syntax_node.h"
#include "diff/diff_syntax_node.h"
#include "sum/sum_syntax_node.h"
#include "multiply/multiply_syntax_node.h"
#include "expression_syntax_node.h"
#include "i_syntax_node.h"
#include "if_expression_syntax_node.h"
#include "print_expression_syntax_node.h"
#include "scope_syntax_node.h"
#include "varible_assigment_syntax_node.h"

class ISyntaxNodeVisitor
{
public:
   virtual void visit( const BolSyntaxNodeSP& ) = 0;
   virtual void visit( const EolSyntaxNodeSP& ) = 0;
   virtual void visit( const PlusSyntaxNodeSP& ) = 0;
   virtual void visit( const MinusSyntaxNodeSP& ) = 0;
   virtual void visit( const AsteriskSyntaxNodeSP& ) = 0;
   virtual void visit( const NumberSyntaxNodeSP& ) = 0;
   virtual void visit( const FSyntaxNodeSP& ) = 0;
   virtual void visit( const SumSyntaxNodeSP& ) = 0;
   virtual void visit( const DiffSyntaxNodeSP& ) = 0;
   virtual void visit( const MultiplySyntaxNodeSP& ) = 0;
   virtual void visit( const SemicolonSyntaxNodeSP& ) = 0;
   virtual void visit( const ExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const ScopeSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCurlyBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const OpenCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const CloseCircleBracketSyntaxNodeSP& ) = 0;
   virtual void visit( const ComputationalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const ConditionalExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const PrintSyntaxNodeSP& ) = 0;
   virtual void visit( const EqualSyntaxNodeSP& ) = 0;
   virtual void visit( const LessSyntaxNodeSP& ) = 0;
   virtual void visit( const MoreSyntaxNodeSP& ) = 0;
   virtual void visit( const IfSyntaxNodeSP& ) = 0;
   virtual void visit( const IfExpressionSyntaxNodeSP& ) = 0;
   virtual void visit( const VaribleAssigmentSyntaxNodeSP& ) = 0;
   virtual void visit( const NameSyntaxNodeSP& ) = 0;
};
using ISyntaxNodeVisitorSP = std::shared_ptr< ISyntaxNodeVisitor >;
