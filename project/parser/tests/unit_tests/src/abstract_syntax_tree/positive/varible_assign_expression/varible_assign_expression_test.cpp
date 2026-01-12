#include "abstract_syntax_tree.h"

#include "lexical_tokens.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_GLOBAL_VARIBLE_ASSIGN, F )
{
   // ARRANGE
   const auto& input = R"""(
      a=1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );

   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, f, lexical_tokens[2] );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[4] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_GLOBAL_VARIBLE_ASSIGN, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      a=1+2;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );

   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );

   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
  
   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[4] };

   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr_lexical_tokens );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, bin_expr, lexical_tokens[2] );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[6] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_GLOBAL_VARIBLE_ASSIGN, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      a=-1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );

   const auto& d = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f = std::make_shared< FSyntaxNode >( d );

   std::vector< LexicalTokens::LexicalToken > un_expr_lexical_tokens{ lexical_tokens[3] };

   const auto& un_expr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, un_expr_lexical_tokens );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, un_expr, lexical_tokens[2] );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_GLOBAL_VARIBLE_ASSIGN, NAME )
{
   // ARRANGE
   const auto& input = R"""(
      a=b;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );

   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name0, name1, lexical_tokens[2] );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[4] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_GLOBAL_VARIBLE_ASSIGN, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      a=foo(1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );

   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& d = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f = std::make_shared< FSyntaxNode >( d );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name1, std::vector< ISyntaxNodeSP >{ f } );

   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name0, function_call, lexical_tokens[2] );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[7] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_LOCAL_VARIBLE_ASSIGN, F )
{
   // ARRANGE
   const auto& input = R"""(
      var a=1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );

   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, f, lexical_tokens[3], VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_LOCAL_VARIBLE_ASSIGN, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      var a=1+2;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );

   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );

   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[6] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
  
   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[5] };

   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr_lexical_tokens );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, bin_expr, lexical_tokens[3], VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[7] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_LOCAL_VARIBLE_ASSIGN, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      var a=-1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );

   const auto& d = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f = std::make_shared< FSyntaxNode >( d );

   std::vector< LexicalTokens::LexicalToken > un_expr_lexical_tokens{ lexical_tokens[4] };

   const auto& un_expr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, un_expr_lexical_tokens );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, un_expr, lexical_tokens[3], VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[6] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_LOCAL_VARIBLE_ASSIGN, NAME )
{
   // ARRANGE
   const auto& input = R"""(
      var a=b;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );

   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
  
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name0, name1, lexical_tokens[3], VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_LOCAL_VARIBLE_ASSIGN, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      var a=foo(1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );

   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
   const auto& d = std::make_shared< IntSyntaxNode >( lexical_tokens[6] );
   const auto& f = std::make_shared< FSyntaxNode >( d );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name1, std::vector< ISyntaxNodeSP >{ f } );

   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name0, function_call, lexical_tokens[3], VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
   const auto& statment = std::make_shared< StatmentSyntaxNode >( varible_assigment, lexical_tokens[8] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
