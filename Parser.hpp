#ifndef PARSE_HPP
#define PARSE_HPP
#include "String.hpp"
#include "Tokenizer.hpp"
#include "Array.hpp"
#include "JSONValue.hpp"
#include "JSONObject.hpp"

// Change to JFA
class Parser
{
private:
    Tokenizer *tokenizer;
    void eat(JSONToken::Type type);

public:
    JSONObject root;
    Parser(JFA::String str);
    ~Parser();
    void parse();
    JSONValue parseValue();
    JSONObject parseObject();
};

#endif // PARSE_HPP