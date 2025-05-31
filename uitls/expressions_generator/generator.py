#!/usr/bin/python3
import random

GRAMMAR = {
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
        ["<number>"]
    ],
    "<number>": [
        ["<digit>"],
        ["<digit>", "<number>"]
    ],
    "<digit>": [[str(d)] for d in range(10)]
}

def generate(grammar, symbol="<expr>", max_depth=10):
    if max_depth <= 0:
        # Если достигли максимальной глубины, выбираем простейшие правила для завершения
        if symbol in ["<expr>", "<term>", "<factor>", "<number>"]:
            if symbol == "<expr>" or symbol == "<term>":
                return generate(grammar, "<factor>", max_depth-1)
            elif symbol == "<factor>":
                return generate(grammar, "<number>", max_depth-1)
            elif symbol == "<number>":
                return generate(grammar, "<digit>", max_depth-1)
        elif symbol == "<digit>":
            return random.choice("0123456789")

    if symbol not in grammar:
        # Терминальный символ
        return symbol

    expansion = random.choice(grammar[symbol])
    return "".join(generate(grammar, sym, max_depth - 1) for sym in expansion)

# Пример использования:
for _ in range(10):
    print(generate(GRAMMAR))
