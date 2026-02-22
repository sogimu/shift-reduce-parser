#include "abstract_syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_FUNCTION_STATMENT, ZERO_ARGUMENT )
{
   // ARRANGE
   const auto& input = R"""(
    function foo()
    {
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[5], lexical_tokens[6]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {}, scope_lexical_tokens );
   std::vector< LexicalTokens::LexicalToken > function_statment_lexical_tokens{ lexical_tokens[1], lexical_tokens[3], lexical_tokens[4] };
   const auto& function_statment = std::make_shared< FunctionStatmentSyntaxNode >( name, 
                                                                                   std::vector< ISyntaxNodeSP >{}, 
                                                                                   scope, function_statment_lexical_tokens );

   AbstractSyntaxTree expected_syntax_tree { function_statment };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_STATMENT, ONE_ARGUMENT )
{
   // ARRANGE
   const auto& input = R"""(
    function foo(a)
    {
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[6], lexical_tokens[7]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {}, scope_lexical_tokens );
   std::vector< LexicalTokens::LexicalToken > function_statment_lexical_tokens{ lexical_tokens[1], lexical_tokens[3], lexical_tokens[5]  };
   const auto& function_statment = std::make_shared< FunctionStatmentSyntaxNode >( name0, 
                                                                                   std::vector< ISyntaxNodeSP >{name1}, 
                                                                                   scope, function_statment_lexical_tokens );

   AbstractSyntaxTree expected_syntax_tree { function_statment };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_STATMENT, TWO_ARGUMENT )
{
   // ARRANGE
   const auto& input = R"""(
    function foo(a,b)
    {
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[2] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
   const auto& name2 = std::make_shared< NameSyntaxNode >( lexical_tokens[6] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[8], lexical_tokens[9]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {}, scope_lexical_tokens );
   std::vector< LexicalTokens::LexicalToken > function_statment_lexical_tokens{ lexical_tokens[1], lexical_tokens[3], lexical_tokens[7]  };
   const auto& function_statment = std::make_shared< FunctionStatmentSyntaxNode >( name0, 
                                                                                   std::vector< ISyntaxNodeSP >{ name1, name2 }, 
                                                                                   scope, function_statment_lexical_tokens );

   AbstractSyntaxTree expected_syntax_tree { function_statment };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
