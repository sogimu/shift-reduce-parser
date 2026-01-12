#include "abstract_syntax_tree.h"

#include "i_syntax_node.h"
#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_F_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      2;
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );
   const auto& statment0 = std::make_shared< StatmentSyntaxNode >( f0, lexical_tokens[3] );
   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
   const auto& statment1 = std::make_shared< StatmentSyntaxNode >( f1, lexical_tokens[5] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[1], lexical_tokens[6]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {statment0, statment1}, scope_lexical_tokens );
   AbstractSyntaxTree expected_syntax_tree { scope };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_F )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      2
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );
   const auto& statment0 = std::make_shared< StatmentSyntaxNode >( f0, lexical_tokens[3] );
   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[4] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
   const auto& statment1 = std::make_shared< StatmentSyntaxNode >( f1 );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[1], lexical_tokens[6]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {statment0, statment1}, scope_lexical_tokens );
   AbstractSyntaxTree expected_syntax_tree { scope };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_VARIBLE_ASSIGMENT )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      a=2
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[2] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );
   const auto& statment0 = std::make_shared< StatmentSyntaxNode >( f0, lexical_tokens[3] );
   const auto& name = std::make_shared< NameSyntaxNode >( lexical_tokens[4] );
   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[6] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, f1, lexical_tokens[5] );
   const auto& statment1 = std::make_shared< StatmentSyntaxNode >( varible_assigment );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens{ lexical_tokens[1], lexical_tokens[7]  };
   const auto& scope = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {statment0, statment1}, scope_lexical_tokens );
   AbstractSyntaxTree expected_syntax_tree { scope };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_SCOPE, NESTED_SCOPE )
{
   // ARRANGE
   const auto& input = R"""(
    {
      { 
        1;
        2;
      }
      3;
      4;
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& d0 = std::make_shared< IntSyntaxNode >( lexical_tokens[3] );
   const auto& f0 = std::make_shared< FSyntaxNode >( d0 );
   const auto& statment0 = std::make_shared< StatmentSyntaxNode >( f0, lexical_tokens[4] );
   const auto& d1 = std::make_shared< IntSyntaxNode >( lexical_tokens[5] );
   const auto& f1 = std::make_shared< FSyntaxNode >( d1 );
   const auto& statment1 = std::make_shared< StatmentSyntaxNode >( f1, lexical_tokens[6] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens0{ lexical_tokens[2], lexical_tokens[7]  };
   const auto& scope0 = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {statment0, statment1}, scope_lexical_tokens0 );
   const auto& d2 = std::make_shared< IntSyntaxNode >( lexical_tokens[8] );
   const auto& f2 = std::make_shared< FSyntaxNode >( d2 );
   const auto& statment2 = std::make_shared< StatmentSyntaxNode >( f2, lexical_tokens[9] );
   const auto& d3 = std::make_shared< IntSyntaxNode >( lexical_tokens[10] );
   const auto& f3 = std::make_shared< FSyntaxNode >( d3 );
   const auto& statment3 = std::make_shared< StatmentSyntaxNode >( f3, lexical_tokens[11] );
   std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens1{ lexical_tokens[1], lexical_tokens[12]  };
   const auto& scope1 = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {scope0, statment2, statment3}, scope_lexical_tokens1 );

   AbstractSyntaxTree expected_syntax_tree { scope1 };

   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_SCOPE, FUNCTION_DECLARATION_FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
    {
      function foo(a)
      {
      }
      foo(1);
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = AbstractSyntaxTree( lexical_tokens );

   // ASSERT
   const auto& name0 = std::make_shared< NameSyntaxNode >( lexical_tokens[3] );
   const auto& name1 = std::make_shared< NameSyntaxNode >( lexical_tokens[5] );
   std::vector< LexicalTokens::LexicalToken > scope0_lexical_tokens{ lexical_tokens[7], lexical_tokens[8]  };
   const auto& scope0 = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {}, scope0_lexical_tokens );
   std::vector< LexicalTokens::LexicalToken > function_statment_lexical_tokens{ lexical_tokens[2]  };
   const auto& function_statment = std::make_shared< FunctionStatmentSyntaxNode >( name0, 
                                                                                   std::vector< ISyntaxNodeSP >{name1}, 
                                                                                   scope0, function_statment_lexical_tokens );

   const auto& statment0 = std::make_shared< StatmentSyntaxNode >( function_statment );
   
   const auto& name2 = std::make_shared< NameSyntaxNode >( lexical_tokens[9] );
   const auto& number = std::make_shared< IntSyntaxNode >( lexical_tokens[11] );
   const auto& f = std::make_shared< FSyntaxNode >( number );
   const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( name2, std::vector< ISyntaxNodeSP >{ f } );
   
   const auto& statment1 = std::make_shared< StatmentSyntaxNode >( function_call, lexical_tokens[13] );
   std::vector< LexicalTokens::LexicalToken > scope1_lexical_tokens{ lexical_tokens[1], lexical_tokens[14]  };
   const auto& scope1 = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP > {statment0, statment1}, scope1_lexical_tokens );

   AbstractSyntaxTree expected_syntax_tree { scope1 };
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
