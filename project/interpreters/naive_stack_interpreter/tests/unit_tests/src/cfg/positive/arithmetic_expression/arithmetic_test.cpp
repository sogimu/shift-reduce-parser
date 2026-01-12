#include "interpreter.h"

#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/equal_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/slash_syntax_node.h"
#include <gtest/gtest.h>
#include <memory>
#include <abstract_syntax_tree.h>
#include <control_flow_graph.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(1;)""";
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& n = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& f = std::make_shared< FSyntaxNode >( n );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( f, lexical_tokens[2] );
   const auto& syntax_tree = AbstractSyntaxTree( statment );

   // ACT
   ControlFlowGraph cfg{ syntax_tree };
   
   // ASSERT
   const auto& expected_n = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& expected_f = std::make_shared< FSyntaxNode >( expected_n );
   const auto& expected_statment = std::make_shared< StatmentSyntaxNode >( expected_f, lexical_tokens[2] );
   ControlFlowGraph expected_cfg{ expected_statment };

   EXPECT_EQ( cfg, expected_cfg );
}

TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, MINUS_INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(-1;)""";
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& n = std::make_shared< DoubleSyntaxNode >( lexical_tokens[2] );
   const auto& f = std::make_shared< FSyntaxNode >( n );
   const auto& unexpr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[1] } );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( unexpr, lexical_tokens[3] );
   AbstractSyntaxTree syntax_tree { statment };

   // ACT
   ControlFlowGraph cfg{ syntax_tree };

   // ASSERT
   const auto& expected_n = std::make_shared< DoubleSyntaxNode >( lexical_tokens[2] );
   const auto& expected_f = std::make_shared< FSyntaxNode >( expected_n );
   const auto& expected_unexpr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[1] } );
   const auto& expected_statment = std::make_shared< StatmentSyntaxNode >( lexical_tokens[3] );
   expected_statment->add_back( expected_f );
   expected_statment->add_back( expected_unexpr );
   ControlFlowGraph expected_cfg{ expected_statment };

   EXPECT_EQ( cfg, expected_cfg );
}

TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, UN_EXPR_LAST )
{
   // ARRANGE
   const auto& input = R"""(1--2;)""";
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& f0 = std::make_shared< FSyntaxNode >( n0 );

   const auto& n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
   const auto& unexpr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f1, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[3] } );

   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f0, unexpr, bin_expr_lexical_tokens );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[5] );
   AbstractSyntaxTree syntax_tree { statment };

   // ACT
   ControlFlowGraph cfg{ syntax_tree };

   // ASSERT
   const auto& expected_n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& expected_f0 = std::make_shared< FSyntaxNode >( expected_n0 );

   const auto& expected_n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[4] );
   const auto& expected_f1 = std::make_shared< FSyntaxNode >( expected_n1 );
   const auto& expected_un_expr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[3] } );

   std::vector< LexicalTokens::LexicalToken > expected_bin_expr_lexical_tokens{ lexical_tokens[2] };
   const auto& expected_bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, expected_bin_expr_lexical_tokens );
   const auto& expected_statment = std::make_shared< StatmentSyntaxNode >( lexical_tokens[5] );
   expected_statment->add_back( expected_f0 );
   expected_statment->add_back( expected_f1 );
   expected_statment->add_back( expected_un_expr );
   expected_statment->add_back( expected_bin_expr );
   ControlFlowGraph expected_cfg{ expected_statment };

   EXPECT_EQ( cfg, expected_cfg );
}

TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, UN_EXPR_NOT_LAST )
{
   // ARRANGE
   const auto& input = R"""(-2-1;)""";
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
   const auto& unexpr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f0, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[1] } );

   const auto& n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( n1 );

   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[3] };
   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, unexpr, f1, bin_expr_lexical_tokens );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[5] );
   AbstractSyntaxTree syntax_tree { statment };

   // ACT
   ControlFlowGraph cfg{ syntax_tree };

   // ASSERT
   const auto& expected_n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[2] );
   const auto& expected_f0 = std::make_shared< FSyntaxNode >( expected_n0 );
   const auto& expected_un_expr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[1] } );

   const auto& expected_n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[4] );
   const auto& expected_f1 = std::make_shared< FSyntaxNode >( expected_n1 );

   std::vector< LexicalTokens::LexicalToken > expected_bin_expr_lexical_tokens{ lexical_tokens[3] };
   const auto& expected_bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, expected_bin_expr_lexical_tokens );
   const auto& expected_statment = std::make_shared< StatmentSyntaxNode >( lexical_tokens[5] );
   expected_statment->add_back( expected_f0 );
   expected_statment->add_back( expected_un_expr );
   expected_statment->add_back( expected_f1 );
   expected_statment->add_back( expected_bin_expr );
   ControlFlowGraph expected_cfg{ expected_statment };

   EXPECT_EQ( cfg, expected_cfg );
}

// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, OPEN_BRACKET_NUMBER_MINUS_NUMBER_DIVIDE_NUMBER_CLOSE_BRACKET )
// {
//    // ARRANGE
//    const auto& input = R"""((5-2/3);)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[2] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[5] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Division, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[3] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f0, bin_expr0, bin_expr1_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, OPEN_BRACKET_NUMBER_MULTIPLY_OPEN_BRACKET_NUMBER_CLOSE_BRACKET_CLOSE_BRACKET )
// {
//    // ARRANGE
//    const auto& input = R"""((1*(8));)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[2] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[3] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Multiply, f0, f1, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, OPEN_BRACKET_NUMBER_CLOSE_BRACKET )
// {
//    // ARRANGE
//    const auto& input = R"""((1);)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n = std::make_shared< NumberSyntaxNode >( lexical_tokens[2] );
//    const auto& f = std::make_shared< FSyntaxNode >( n );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( f, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ONE_PLUS )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& f0 = std::make_shared< FSyntaxNode >( n0 );

   const auto& n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[3] );
   const auto& f1 = std::make_shared< FSyntaxNode >( n1 );

   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr_lexical_tokens );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
   AbstractSyntaxTree syntax_tree { statment };

   // ACT
   ControlFlowGraph cfg{ syntax_tree };

   // ASSERT
   const auto& expected_n0 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[1] );
   const auto& expected_f0 = std::make_shared< FSyntaxNode >( expected_n0 );

   const auto& expected_n1 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[3] );
   const auto& expected_f1 = std::make_shared< FSyntaxNode >( expected_n1 );

   std::vector< LexicalTokens::LexicalToken > expected_bin_expr_lexical_tokens{ lexical_tokens[2] };
   const auto& expected_bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, expected_bin_expr_lexical_tokens );
   const auto& expected_statment = std::make_shared< StatmentSyntaxNode >( lexical_tokens[4] );
   expected_statment->add_back( expected_f0 );
   expected_statment->add_back( expected_f1 );
   expected_statment->add_back( expected_bin_expr );
   ControlFlowGraph expected_cfg{ expected_statment };

   EXPECT_EQ( cfg, expected_cfg );
}

// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_F_EQUAL_F )
// {
//    // ARRANGE
//    const auto& input = R"""(1==2;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2], lexical_tokens[3] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Equal, f0, f1, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[5] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_F_EQUAL_NAME )
// {
//    // ARRANGE
//    const auto& input = R"""(1==a;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2], lexical_tokens[3] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Equal, f0, name, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[5] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_F_LESS_NAME )
// {
//    // ARRANGE
//    const auto& input = R"""(1<a;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Less, f0, name, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_F_MORE_NAME )
// {
//    // ARRANGE
//    const auto& input = R"""(1>a;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::More, f0, name, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_BIN_EXPR_EQUAL_BIN_EXPR )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2==3+4;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& n3 = std::make_shared< NumberSyntaxNode >( lexical_tokens[8] );
//    const auto& f3 = std::make_shared< FSyntaxNode >( n3 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[7] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[4], lexical_tokens[5] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Equal, bin_expr0, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[9] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_BIN_EXPR_MORE_EQUAL_BIN_EXPR )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2>=3+4;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& n3 = std::make_shared< NumberSyntaxNode >( lexical_tokens[8] );
//    const auto& f3 = std::make_shared< FSyntaxNode >( n3 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[7] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[4], lexical_tokens[5] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::MoreEqual, bin_expr0, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[9] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_BIN_EXPR_LESS_EQUAL_BIN_EXPR )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2<=3+4;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& n3 = std::make_shared< NumberSyntaxNode >( lexical_tokens[8] );
//    const auto& f3 = std::make_shared< FSyntaxNode >( n3 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[7] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[4], lexical_tokens[5] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::LessEqual, bin_expr0, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[9] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_BIN_EXPR_LESS_BIN_EXPR )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2<3+4;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& n3 = std::make_shared< NumberSyntaxNode >( lexical_tokens[7] );
//    const auto& f3 = std::make_shared< FSyntaxNode >( n3 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[6] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Less, bin_expr0, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CONDITION_BIN_EXPR_MORE_BIN_EXPR )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2>3+4;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& n3 = std::make_shared< NumberSyntaxNode >( lexical_tokens[7] );
//    const auto& f3 = std::make_shared< FSyntaxNode >( n3 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[6] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::More, bin_expr0, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, F_PLUS_VARIBLE )
// {
//    // ARRANGE
//    const auto& input = R"""(1+a;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, name, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, F_PLUS_FUNCTION_CALL )
// {
//    // ARRANGE
//    const auto& input = R"""(1+foo(2);)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//    const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ f1 } );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, function_call, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[7] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ONE_DIVISION )
// {
//    // ARRANGE
//    const auto& input = R"""(6/2;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Division, f0, f1, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, MANY_PLUSs )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2+3;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[6] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, MANY_MINUSES )
// {
//    // ARRANGE
//    const auto& input = R"""(1-2-3;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[6] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ADVANCE_EXPRESSION0 )
// {
//    // ARRANGE
//    const auto& input = R"""(1+2*3;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[5] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Multiply, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[6] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ADVANCE_EXPRESSION1 )
// {
//    // ARRANGE
//    const auto& input = R"""(x-1/x;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
//
//    const auto& number = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f = std::make_shared< FSyntaxNode >( number );
//
//    const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[5] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Division, f, name1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, name0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[6] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ADVANCE_EXPRESSION2 )
// {
//    // ARRANGE
//    const auto& input = R"""(1-x*a-c;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& number = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f = std::make_shared< FSyntaxNode >( number );
//
//    const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
//
//    const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[5] );
//
//    const auto& name2 = std::make_shared< NameSyntaxNode >( lexical_tokens[7] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Multiply, name0, name1, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[6] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, bin_expr0, name2, bin_expr1_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr2_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr2 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f, bin_expr1, bin_expr2_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr2, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CIRCLE_CASE0 )
// {
//    // ARRANGE
//    const auto& input = R"""(1+(2*3);)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& open_circle_bracket = std::make_shared< OpenCircleBracketSyntaxNode >( lexical_tokens[3] );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& close_circle_bracket = std::make_shared< CloseCircleBracketSyntaxNode >( lexical_tokens[7] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[5] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Multiply, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, CIRCLE_CASE1 )
// {
//    // ARRANGE
//    const auto& input = R"""(1+(2+3);)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& open_circle_bracket = std::make_shared< OpenCircleBracketSyntaxNode >( lexical_tokens[3] );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    const auto& n2 = std::make_shared< NumberSyntaxNode >( lexical_tokens[6] );
//    const auto& f2 = std::make_shared< FSyntaxNode >( n2 );
//
//    const auto& close_circle_bracket = std::make_shared< CloseCircleBracketSyntaxNode >( lexical_tokens[7] );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[5] };
//    const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f1, f2, bin_expr0_lexical_tokens );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, bin_expr0, bin_expr1_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr1, lexical_tokens[8] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// TEST( NAIVE_STACK_INTERPRETER_CFG_POSITIVE_ARITHMETIC, ONE_MINUS )
// {
//    // ARRANGE
//    const auto& input = R"""(1-2;)""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[1] );
//    const auto& f0 = std::make_shared< FSyntaxNode >( n0 );
//
//    const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
//    const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
//
//    std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[2] };
//    const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Substruction, f0, f1, bin_expr_lexical_tokens );
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( bin_expr, lexical_tokens[4] );
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
