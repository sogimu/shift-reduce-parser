#include <gtest/gtest.h>
#include "utils/utils.h"
#include "nonterminals/object_syntax_node.h"
#include "terminals/string_syntax_node.h"

using namespace std;

TEST( SYNTAX_TREE_OBJECT, FROM_TWO_INT )
{
   // ARRANGE
   const auto& input = R"""(
    {"key": 12, "key1": 42};
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& string0 = std::make_shared< StringSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( string0 );
   const auto& number0 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( number0 );
  
   const auto& string1 = std::make_shared< StringSyntaxNode >( lexical_tokens[6] );
   const auto& f2 = std::make_shared< FSyntaxNode >( string1 );
   const auto& number1 = std::make_shared< IntSyntaxNode >( lexical_tokens[8] );
   const auto& f3 = std::make_shared< FSyntaxNode >( number1 );
   
   std::vector< LexicalTokens::LexicalToken > object_lexical_tokens
   {
      lexical_tokens[1], lexical_tokens[9]
   };
   const auto& object = std::make_shared< ObjectSyntaxNode >( std::map< std::string, ISyntaxNodeSP >{ {"key", f1}, {"key1", f1} }, object_lexical_tokens );
   
   const auto& statment = std::make_shared< StatmentSyntaxNode >( object, lexical_tokens[10] );
  
   AbstractSyntaxTree expected_syntax_tree { statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

// TEST( SYNTAX_TREE_OBJECT, EMPTY )
// {
//    // ARRANGE
//    const auto& input = R"""(
//     {};
//    )""";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );
//
//    // ASSERT
//    std::vector< LexicalTokens::LexicalToken > object_lexical_tokens
//    {
//       lexical_tokens[1], lexical_tokens[2]
//    };
//    const auto& object = std::make_shared< ObjectSyntaxNode >( std::vector< ISyntaxNodeSP >{}, object_lexical_tokens );
//
//    const auto& statment = std::make_shared< StatmentSyntaxNode >( object, lexical_tokens[3] );
//
//    AbstractSyntaxTree expected_syntax_tree { statment };
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
