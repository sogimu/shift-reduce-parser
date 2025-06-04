#!/usr/bin/python3
import random

GRAMMAR = {
    "<program>": [
        ["<stmt_list>"]
    ],
    "<stmt_list>": [
        ["<stmt>"],
        ["<stmt>", ";", "<stmt_list>"]
    ],
    "<stmt>": [
        ["<assign_stmt>"],
        ["<if_stmt>"],
        ["<while_stmt>"],
        ["<expr>"]
    ],
    "<assign_stmt>": [
        ["<var>", "=", "<expr>"]
    ],
    "<if_stmt>": [
        ["if", "(", "<expr>", ")", "{", "<stmt_list>", "}"]
    ],
    "<while_stmt>": [
        ["while", "(", "<expr>", ")", "{", "<stmt_list>", "}"]
    ],
    "<expr>": [
        ["<expr>", "+", "<term>"],
        ["<expr>", "-", "<term>"],
        ["<term>"]
    ],
    "<term>": [
        ["<term>", "*", "<factor>"],
        ["<term>", "/", "<factor>"],
        ["<factor>"]
    ],
    "<factor>": [
        ["(", "<expr>", ")"],
        ["<number>"],
        ["<var>"]
    ],
    "<number>": [
        ["<digit>"],
        ["<digit>", "<number>"]
    ],
    "<digit>": [[str(d)] for d in range(10)],
    "<var>": [
        ["x"],
        ["y"],
        ["z"],
        ["a"],
        ["b"],
        ["c"]
    ]
}

def generate(grammar, symbol="<program>", max_depth=10):
    if max_depth <= 0:
        # При достижении глубины выбираем простейшие варианты
        if symbol in ["<expr>", "<term>", "<factor>", "<number>", "<stmt_list>", "<stmt>"]:
            if symbol == "<expr>" or symbol == "<term>":
                return generate(grammar, "<factor>", max_depth-1)
            elif symbol == "<factor>":
                # Чтобы не уходить в рекурсию, выбираем число или переменную
                return random.choice([generate(grammar, "<number>", max_depth-1), generate(grammar, "<var>", max_depth-1)])
            elif symbol == "<number>":
                return generate(grammar, "<digit>", max_depth-1)
            elif symbol == "<stmt_list>":
                return generate(grammar, "<stmt>", max_depth-1)
            elif symbol == "<stmt>":
                # Для stmt выбираем присваивание или выражение
                return generate(grammar, random.choice(["<assign_stmt>", "<expr>"]), max_depth-1)
        elif symbol == "<digit>" or symbol == "<var>":
            return random.choice(grammar[symbol])[0]

    if symbol not in grammar:
        # Терминальный символ (например, ключевые слова, знаки)
        return symbol

    expansion = random.choice(grammar[symbol])
    return "".join(generate(grammar, sym, max_depth - 1) for sym in expansion)

# Пример использования:
for _ in range(5):
    print(generate(GRAMMAR))
