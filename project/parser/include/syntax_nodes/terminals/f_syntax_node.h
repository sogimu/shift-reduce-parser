#pragma once

#include <variant>
#include <iostream>
#include <string>

#include "terminals/minus_syntax_node.h"
#include "terminals/double_syntax_node.h"
#include "terminals/int_syntax_node.h"
#include "terminals/string_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class FSyntaxNodeValue
{
public:
    // Конструктор-шаблон для неявного создания из double, int или std::string
    template<typename T>
    FSyntaxNodeValue( T&& val ) 
        : value_{ std::forward<T>( val ) }
    { 
    }

    // Доступ к внутреннему варианту (если нужно)
    const std::variant<double, int, std::string>& get() const
    { 
        return value_;
    }

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const FSyntaxNodeValue& val);
    friend bool operator==(const FSyntaxNodeValue& lhs, const FSyntaxNodeValue& rhs);
private:
    std::variant<double, int, std::string> value_;
};

inline std::ostream& operator<<(std::ostream& os, const FSyntaxNodeValue& value)
{
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, double>) {
            os << arg; 
        } else if constexpr (std::is_same_v<T, int>) {
            os << arg;
        } else if constexpr (std::is_same_v<T, std::string>) {
            os << arg;
        }
    }, value.get());    
    return os;
}

inline bool operator==(const FSyntaxNodeValue& lhs, const FSyntaxNodeValue& rhs)
{
    return lhs.value_ == rhs.value_;
}

class FSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FSyntaxNode >
{
public:
   FSyntaxNode( const FSyntaxNode& f_syntax_node );
   FSyntaxNode( const MinusSyntaxNodeSP& minus, const DoubleSyntaxNodeSP& number );
   FSyntaxNode( const DoubleSyntaxNodeSP& number );
   FSyntaxNode( const MinusSyntaxNodeSP& minus, const IntSyntaxNodeSP& number );
   FSyntaxNode( const IntSyntaxNodeSP& number );
   FSyntaxNode( const StringSyntaxNodeSP& string );

   FSyntaxNodeValue value() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;

private:
   FSyntaxNodeValue mValue;
};

using FSyntaxNodeSP = std::shared_ptr< FSyntaxNode >;
