#include "abstract_syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_PRINT, F )
{
   // ARRANGE
   const auto& input = R"""(
      print(1);
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
   const auto& print = std::make_shared< PrintStatmentSyntaxNode >( f );
   
   AbstractSyntaxTree expected_syntax_tree { print };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_PRINT, VARIBALE )
{
   // ARRANGE
   const auto& input = R"""(
      print(a);
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& varible = std::make_shared< VaribleSyntaxNode >( name, name->lexical_tokens() );
   const auto& print = std::make_shared< PrintStatmentSyntaxNode >( varible );
   
   AbstractSyntaxTree expected_syntax_tree { print };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_PRINT, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      print(foo());
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name, std::vector< ISyntaxNodeSP >{} );
   
   const auto& print = std::make_shared< PrintStatmentSyntaxNode >( function_call );
   
   AbstractSyntaxTree expected_syntax_tree { print };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
