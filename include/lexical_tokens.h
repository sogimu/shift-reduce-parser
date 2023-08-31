#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <stack>
#include <map>
#include <iomanip>
#include <functional>
#include <optional>

#include "enums.h"

class LexicalTokens
{
public:
    struct LexicalToken
    {
        std::string text;
        Token_Type type;
    };

    LexicalTokens(const std::string& text)
    {
        std::vector<LexicalToken> result;
        result.emplace_back(LexicalToken{"", Token_Type::BOL});

        Token_Type current_token_type = Token_Type::NO;
        Token_Type next_token_type = Token_Type::NO;

        auto create_expression_generator = [](const auto& text)
        {
            auto it = text.begin();
            auto sentinel = text.end();
            auto next_char = [it, sentinel]() mutable ->char
            {
                if(it == sentinel)
                    return '\n';
                auto current_it = it++;
                if(current_it != sentinel)
                    return *current_it;
                else
                    return '\n';
            };

            struct Chars
            {
                char current;
                char next;
            };

            Chars chars;
            chars.next = next_char();

            return [next_char, chars]() mutable->Chars
            {
                chars.current = std::exchange(chars.next, next_char());
                return chars;
            };
        };

        auto next_chars = create_expression_generator(text);
        auto chars = next_chars();
        while( chars.current!='\n' )
        {
            if(terminals.count(chars.current))
            {
                Token_Type terminal_token_type = Token_Type::NO;

                switch (chars.current) {
                case '+':
                {
                    terminal_token_type = Token_Type::PLUS;
                }; break;
                case '-':
                {
                    terminal_token_type = Token_Type::MINUS;
                }; break;
                case '*':
                {
                    terminal_token_type = Token_Type::MULTIPLY;
                }; break;
                case '/':
                {
                    terminal_token_type = Token_Type::DIVIDE;
                }; break;
                case '(':
                {
                    terminal_token_type = Token_Type::OPEN_BRACKET;
                }; break;
                case ')':
                {
                    terminal_token_type = Token_Type::CLOSE_BRACKET;
                }; break;
                case '=':
                {
                    terminal_token_type = Token_Type::EQUAL;
                }; break;
                case ';':
                {
                    terminal_token_type = Token_Type::SEMICOLON;
                }; break;

                default:
                {
                }
                }

                result.emplace_back(LexicalToken{std::string{chars.current}, terminal_token_type});
                current_token_type = terminal_token_type;
                chars = next_chars();
            }
            else if(didgits.count(chars.current))
            {
                std::string token;
                for(; didgits.count(chars.current); chars = next_chars())
                {
                    token += chars.current;
                }
                current_token_type = Token_Type::INT;
                result.emplace_back(LexicalToken{token, Token_Type::INT});
            }
            else if(alphabet.count(chars.current))
            {
                std::string token;
                for(; alphabet.count(chars.current) || didgits.count(chars.current); chars = next_chars())
                {
                    token += chars.current;
                }
                current_token_type = Token_Type::NAME;
                result.emplace_back(LexicalToken{token, Token_Type::NAME});
            }
        }

        result.emplace_back("", Token_Type::EOL);

        tokens = result;
    }

    std::vector<LexicalToken> list() const
    {
        return tokens;
    }

private:
    std::vector<LexicalToken> tokens;

    const std::set<char> didgits
    {
        '1','2','3','4','5','6','7','8','9','0'
    };

    const std::set<char> alphabet
    {
        'a','b','c','d','e','f','g','h','i','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'v', 'x', 'y', 'z',
        'A','B','C','D','E','F','G','H','I','K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'X', 'Y', 'Z'
    };

    const std::set<char> terminals
    {
        '+','-','/','*','(',')','=',';'
    };
};
