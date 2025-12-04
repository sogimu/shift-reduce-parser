#include "abstract_syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_RETURN_STATMENT, F )
{
   // ARRANGE
   const auto& input = R"""(
      return 1;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& number = std::make_shared< NumberSyntaxNode >( lexical_tokens[2] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
   const auto& return_syntax_node = std::make_shared< ReturnStatmentSyntaxNode >( f, lexical_tokens[1] );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( return_syntax_node, lexical_tokens[3] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_RETURN_STATMENT, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      return 1+2;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& n0 = std::make_shared< NumberSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( n0 );

   const auto& n1 = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( n1 );
  
   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[3] };

   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr_lexical_tokens );
   const auto& return_syntax_node = std::make_shared< ReturnStatmentSyntaxNode >( bin_expr, lexical_tokens[1] );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( return_syntax_node, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_RETURN_STATMENT, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      return -1;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& n = std::make_shared< NumberSyntaxNode >( lexical_tokens[3] );
   const auto& f = std::make_shared< FSyntaxNode >( n );

   std::vector< LexicalTokens::LexicalToken > un_expr_lexical_tokens{ lexical_tokens[2] };

   const auto& un_expr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, un_expr_lexical_tokens );
   const auto& return_syntax_node = std::make_shared< ReturnStatmentSyntaxNode >( un_expr, lexical_tokens[1] );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( return_syntax_node, lexical_tokens[4] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_RETURN_STATMENT, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      return foo(1);
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );
   const auto& n = std::make_shared< NumberSyntaxNode >( lexical_tokens[4] );
   const auto& f = std::make_shared< FSyntaxNode >( n );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ f } );
   const auto& return_syntax_node = std::make_shared< ReturnStatmentSyntaxNode >( function_call, lexical_tokens[1] );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( return_syntax_node, lexical_tokens[6] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_RETURN_STATMENT, NAME )
{
   // ARRANGE
   const auto& input = R"""(
      return a;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );
   const auto& return_syntax_node = std::make_shared< ReturnStatmentSyntaxNode >( name, lexical_tokens[1] );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( return_syntax_node, lexical_tokens[3] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
