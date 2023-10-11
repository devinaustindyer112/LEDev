#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "String.hpp"

struct JSONToken
{
    enum class Type
    {
        LBRACE,
        RBRACE,
        LBRACKET,
        RBRACKET,
        COMMA,
        COLON,
        STRING,
    };
    JSONToken::Type type;
    JFA::String value;
};

class Tokenizer
{
private:
    JFA::String str;
    int index;

public:
    Tokenizer();
    Tokenizer(JFA::String str);
    JSONToken next();
    bool hasNext();
};

#endif // TOKENIZER_HPP