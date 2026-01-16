#include "nonterminals/array_syntax_node.h"
#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_ARRAY, FROM_TWO_INT )
{
   // ARRANGE
   const auto& input = R"""(
    [1,2,3.4];
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& number0 = std::make_shared< IntSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( number0 );
   const auto& number1 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( number1 );
   const auto& number2 = std::make_shared< DoubleSyntaxNode >( lexical_tokens[6] );
   const auto& f2 = std::make_shared< FSyntaxNode >( number2 );
   
   std::vector< LexicalTokens::LexicalToken > array_lexical_tokens
   {
      lexical_tokens[1], lexical_tokens[7]
   };
   const auto& array = std::make_shared< ArraySyntaxNode >( std::vector< ISyntaxNodeSP >{ f0, f1, f2 }, array_lexical_tokens );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( array, lexical_tokens[8] );
  
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_ARRAY, EMPTY )
{
   // ARRANGE
   const auto& input = R"""(
    [];
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   std::vector< LexicalTokens::LexicalToken > array_lexical_tokens
   {
      lexical_tokens[1], lexical_tokens[2]
   };
   const auto& array = std::make_shared< ArraySyntaxNode >( std::vector< ISyntaxNodeSP >{}, array_lexical_tokens );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( array, lexical_tokens[3] );
  
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
