#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ZERO_VARIBLE )
{
   // ARRANGE
   const auto& input = R"""(
    foo();
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{} );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[4] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_VARIBLE )
{
   // ARRANGE
   const auto& input = R"""(
    foo(a);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name0, std::vector< ISyntaxNodeSP >{ name1 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_VARIBLIES )
{
   // ARRANGE
   const auto& input = R"""(
    foo(a,b);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& name2 = std::make_shared< NameSyntaxNode >( lexical_tokens[5] );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name0, std::vector< ISyntaxNodeSP >{ name1, name2 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[7] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_F )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ f } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[5] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_F )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1,2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& number0 = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f0 = std::make_shared< FSyntaxNode >( number0 );
   const auto& number1 = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f1 = std::make_shared< FSyntaxNode >( number1 );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ f0, f1 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[7] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1+2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );

   const auto& plus = std::make_shared< PlusSyntaxNode >( lexical_tokens[4] );
   
   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
  
   std::vector< LexicalTokens::LexicalToken > bin_expr_lexical_tokens{ lexical_tokens[4] };
   const auto& bin_expr = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr_lexical_tokens );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ bin_expr } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[7] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1+2,3+4);
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
  
   std::vector< LexicalTokens::LexicalToken > bin_expr0_lexical_tokens{ lexical_tokens[4] };
   const auto& bin_expr0 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f0, f1, bin_expr0_lexical_tokens );
   const auto& d2 = std::make_shared< IntSyntaxNode >( lexical_tokens[7] );
   const auto& f2 = std::make_shared< FSyntaxNode >( d2 );

   const auto& d3 = std::make_shared< IntSyntaxNode >( lexical_tokens[9] );
   const auto& f3 = std::make_shared< FSyntaxNode >( d3 );
  
   std::vector< LexicalTokens::LexicalToken > bin_expr1_lexical_tokens{ lexical_tokens[8] };
   const auto& bin_expr1 = std::make_shared< BinExprSyntaxNode >( BinExprSyntaxNode::Type::Addition, f2, f3, bin_expr1_lexical_tokens );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ bin_expr0, bin_expr1 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[11] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(-1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& d = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f = std::make_shared< FSyntaxNode >( d );
   const auto& unexpr = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[3] } );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ unexpr } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[6] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(-1,-2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );
   const auto& unexpr0 = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f0, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[3] } );

   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[7] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
   const auto& unexpr1 = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f1, std::vector<LexicalTokens::LexicalToken>{ lexical_tokens[6] } );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{ unexpr0, unexpr1 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[9] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
    foo(bar(1));
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   
   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
   const auto& function_call0 = std::make_shared< FunctionCallSyntaxNode >( name1, std::vector< ISyntaxNodeSP >{ f } );
   
   const auto& function_call1 = std::make_shared< FunctionCallSyntaxNode >( name0, std::vector< ISyntaxNodeSP >{ function_call0 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call1, lexical_tokens[8] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_FUNCTION_CALLS )
{
   // ARRANGE
   const auto& input = R"""(
    foo( bar(1), zigbee(2) );
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[1] );
   
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] ); 
   const auto& number0 = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f0 = std::make_shared< FSyntaxNode >( number0 );
   const auto& function_call0 = std::make_shared< FunctionCallSyntaxNode >( name1, std::vector< ISyntaxNodeSP >{ f0 } );
   
   const auto& name2 = std::make_shared< NameSyntaxNode >( lexical_tokens[8] ); 
   const auto& number1 = std::make_shared< IntSyntaxNode >( lexical_tokens[10] );
   const auto& f1 = std::make_shared< FSyntaxNode >( number1 );
   const auto& function_call1 = std::make_shared< FunctionCallSyntaxNode >( name2, std::vector< ISyntaxNodeSP >{ f1 } );
   
   const auto& function_call2 = std::make_shared< FunctionCallSyntaxNode >( name0, std::vector< ISyntaxNodeSP >{ function_call0, function_call1 } );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( function_call2, lexical_tokens[13] );
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

