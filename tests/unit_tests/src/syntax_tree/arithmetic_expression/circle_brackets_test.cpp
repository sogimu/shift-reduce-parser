// #include "utils/utils.h"
//
// #include <gtest/gtest.h>
//
// using namespace std;
//
// TEST( SYNTAX_TREE_CIRCLE_BRACKETS, SUM )
// {
//    // ARRANGE
//    const auto& input = "(1+2);";
//
//    // ACT
//    const auto& lexical_tokens = LexicalTokens( input );
//    const auto& syntax_tree = SyntaxTree( lexical_tokens );
//
//    // ASSERT
//    const auto& expected_syntax_tree_description = R"""(
//       {
//         "ScopeSyntaxNode": [
//           {
//             "ExpressionSyntaxNode": [
//               {
//                 "ComputationalExpressionSyntaxNode": [
//                   {
//                     "ESyntaxNode": [
//                       {
//                         "SumSyntaxNode": [
//                           {
//                             "ComputationalExpressionSyntaxNode": [
//                               {
//                                 "FSyntaxNode": [
//                                    1
//                                 ]
//                               }
//                             ]
//                           },
//                           {
//                             "ComputationalExpressionSyntaxNode": [
//                               {
//                                 "FSyntaxNode": [
//                                    2
//                                 ]
//                               }
//                             ]
//                           }
//                         ]
//                       }
//                     ]
//                   }
//                 ]
//               }
//             ]
//           }
//         ]
//       }
//       )""";
//
//    const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
//    std::cout << syntax_tree.to_string() << std::endl;
//    std::cout << expected_syntax_tree.to_string() << std::endl;
//    EXPECT_EQ( syntax_tree, expected_syntax_tree );
// }
//
// // TEST( SYNTAX_TREE_CIRCLE_BRACKETS, ADVANCE_EXPRESSION )
// // {
// //    // ARRANGE
// //    const auto& input = R"""((1/2)*2;)""";
// //
// //    // ACT
// //    const auto& lexical_tokens = LexicalTokens( input );
// //
// //    // ASSERT
// //    LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
// //                                             { "(", Token_Type::OPEN_CIRCLE_BRACKET },
// //                                             { "1", Token_Type::INT },
// //                                             { "/", Token_Type::DIVIDE },
// //                                             { "2", Token_Type::INT },
// //                                             { ")", Token_Type::CLOSE_CIRCLE_BRACKET },
// //                                             { "*", Token_Type::MULTIPLY },
// //                                             { "2", Token_Type::INT },
// //                                             { ";", Token_Type::SEMICOLON },
// //                                             { "", Token_Type::EOL } } };
// //    EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
// // }
