#include "Tokenizer.hpp"
#include "String.hpp"

Tokenizer::Tokenizer()
{
    this->str = "";
    this->index = 0;
}

Tokenizer::Tokenizer(JFA::String str)
{
    // This is breaking everything
    this->str = str.replaceAll(" ", "");
    this->index = 0;
}

JSONToken Tokenizer::next()
{
    if (this->index >= this->str.length())
    {
        // throw "No more tokens";
    }

    JSONToken token;
    char c = this->str[this->index];
    if (c == '{')
    {
        this->index++;
        token.type = JSONToken::Type::LBRACE;
        token.value = c;
    }
    else if (c == '}')
    {
        this->index++;
        token.type = JSONToken::Type::RBRACE;
        token.value = c;
    }
    else if (c == '[')
    {
        this->index++;
        token.type = JSONToken::Type::LBRACKET;
        token.value = c;
    }
    else if (c == ']')
    {
        this->index++;
        token.type = JSONToken::Type::RBRACKET;
        token.value = c;
    }
    else if (c == ':')
    {
        this->index++;
        token.type = JSONToken::Type::COLON;
        token.value = c;
    }
    else if (c == ',')
    {
        this->index++;
        token.type = JSONToken::Type::COMMA;
        token.value = c;
    }
    else if (c == '"')
    {
        JFA::String str = "";
        this->index++;
        while (this->index < this->str.length())
        {
            c = this->str[this->index];
            if (c == '"')
            {
                this->index++;
                break;
            }
            else
            {
                str = str + c;
                this->index++;
            }
        }
        token.type = JSONToken::Type::STRING;
        token.value = str;
    }
    return token;
}

bool Tokenizer::hasNext()
{
    return this->index < this->str.length();
}