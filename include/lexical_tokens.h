#pragma once

#include "enums.h"

#include <optional>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

class LexicalTokens
{
public:
   struct LexicalToken
   {
      std::string text;
      Token_Type type;
      bool operator==( const LexicalToken& token ) const
      {
         return token.type == type && token.text == text;
      }
   };

   LexicalTokens( const std::string& text )
   {
      std::vector< LexicalToken > result;
      result.emplace_back( LexicalToken{ "", Token_Type::BOL } );

      Token_Type current_token_type = Token_Type::NO;
      Token_Type next_token_type = Token_Type::NO;

      auto create_expression_generator = []( const auto& text )
      {
         auto it = text.begin();
         auto sentinel = text.end();
         auto next_char = [ it, sentinel ]() mutable -> std::optional< char >
         {
            if( it == sentinel )
               return {};
            auto current_it = it++;
            if( current_it != sentinel )
               return *current_it;
            else
               return {};
         };

         struct Chars
         {
            std::optional< char > current;
            std::optional< char > next;
         };

         Chars chars;
         chars.next = next_char();

         return [ next_char, chars ]() mutable -> Chars
         {
            chars.current = std::exchange( chars.next, next_char() );
            return chars;
         };
      };

      auto next_chars = create_expression_generator( text );
      auto chars = next_chars();
      while( chars.current.has_value() )
      {
         if( terminals.count( chars.current.value() ) )
         {
            Token_Type terminal_token_type = Token_Type::NO;

            switch( chars.current.value() )
            {
            case '+':
            {
               terminal_token_type = Token_Type::PLUS;
            };
            break;
            case '-':
            {
               terminal_token_type = Token_Type::MINUS;
            };
            break;
            case '*':
            {
               terminal_token_type = Token_Type::ASTERISK;
            };
            break;
            case '/':
            {
               terminal_token_type = Token_Type::SLASH;
            };
            break;
            case '(':
            {
               terminal_token_type = Token_Type::OPEN_CIRCLE_BRACKET;
            };
            break;
            case ')':
            {
               terminal_token_type = Token_Type::CLOSE_CIRCLE_BRACKET;
            };
            break;
            case '{':
            {
               terminal_token_type = Token_Type::OPEN_CURLY_BRACKET;
            };
            break;
            case '}':
            {
               terminal_token_type = Token_Type::CLOSE_CURLY_BRACKET;
            };
            break;
            case '=':
            {
               terminal_token_type = Token_Type::EQUAL;
            };
            break;
            case '<':
            {
               terminal_token_type = Token_Type::LESS;
            };
            break;
            case '>':
            {
               terminal_token_type = Token_Type::MORE;
            };
            break;
            case ';':
            {
               terminal_token_type = Token_Type::SEMICOLON;
            };
            break;

            default:
            {
            }
            }

            result.emplace_back( LexicalToken{ std::string{ chars.current.value() }, terminal_token_type } );
            current_token_type = terminal_token_type;
            chars = next_chars();
         }
         else if( didgits.count( chars.current.value() ) )
         {
            std::string token;
            for( ; chars.current && didgits.count( chars.current.value() ); chars = next_chars() )
            {
               token += chars.current.value();
            }
            current_token_type = Token_Type::INT;
            result.emplace_back( LexicalToken{ token, Token_Type::INT } );
         }
         else if( alphabet.count( chars.current.value() ) )
         {
            std::string token;
            for( ; alphabet.count( chars.current.value() ) || didgits.count( chars.current.value() ); chars = next_chars() )
            {
               token += chars.current.value();
            }
            if( token_by_text.contains( token ) )
            {
               result.emplace_back( LexicalToken{ token, token_by_text.at( token ) } );
            }
            else
            {
               current_token_type = Token_Type::NAME;
               result.emplace_back( LexicalToken{ token, Token_Type::NAME } );
            }
         }
         else
         {
            chars = next_chars();
         }
      }

      result.emplace_back( "", Token_Type::EOL );

      tokens = result;
   }

   LexicalTokens( const std::vector< LexicalToken >& tokens )
   {
      this->tokens = tokens;
   }

   std::vector< LexicalToken > list() const
   {
      return tokens;
   }

   bool operator==( const LexicalTokens& lexical_tokens ) const
   {
      return list() == lexical_tokens.list();
   }

private:
   std::vector< LexicalToken > tokens;

   const std::set< char > didgits{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

   const std::set< char > alphabet{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

   const std::set< char > terminals{ '+', '-', '/', '*', '(', ')', '=', '<', '>', ';', '{', '}' };

   const std::unordered_map< std::string, Token_Type > token_by_text{ { "if", Token_Type::IF }, { "while", Token_Type::WHILE }, { "print", Token_Type::PRINT } };
};
