#include "abstract_syntax_tree.h"

#include "syntax_exception.hpp"
#include <gtest/gtest.h>
#include "utils/utils.h"
#include "syntax_exception.hpp"

using namespace std;

TEST( SYNTAX_TREE_NEGATIVE_BIN_EXPR, TEST0 )
{
   // ARRANGE
   const auto& input = R"""(1+-*4;)""";
   const auto& lexical_tokens = LexicalTokens( input );

   //ACT and ASSERT
   try 
   {
     AbstractSyntaxTree tree( lexical_tokens );
   } 
   catch (const SyntaxException& exception)
   {
        std::cout << exception.what() << std::endl;
       EXPECT_STREQ( exception.what(), "Stack has more that on node and no one grammars may reduce current stack. It's seems that there is syntax error in program!" );
       SUCCEED() << "Got exception as expected";
       return;
   }
   FAIL() << "Was expected exception with message but got no exception";
}

TEST( SYNTAX_TREE_NEGATIVE_BIN_EXPR, TEST1 )
{
   // ARRANGE
   const auto& input = R"""(1+*;;;;;;)""";
   const auto& lexical_tokens = LexicalTokens( input );

   //ACT and ASSERT
   try 
   {
     AbstractSyntaxTree tree( lexical_tokens );
   } 
   catch (const SyntaxException& exception)
   {
        std::cout << exception.what() << std::endl;
       EXPECT_STREQ( exception.what(), "Stack has more that on node and no one grammars may reduce current stack. It's seems that there is syntax error in program!" );
       SUCCEED() << "Got exception as expected";
       return;
   }
   FAIL() << "Was expected exception with message but got no exception";
}
