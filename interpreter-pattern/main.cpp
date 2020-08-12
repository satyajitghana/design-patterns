/**
 * source: http://www.vishalchovatiya.com/interpreter-design-pattern-in-modern-cpp/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

struct Token {
    enum Type {
        integer, plus, minus, lparen, rparen
    };
    Type m_type;
    std::string m_text;

    Token(Type typ, const std::string& txt) : m_type(typ), m_text(txt) {}

    friend std::ostream& operator<<(std::ostream& os, const Token& o) {
        return os << "`" << o.m_text << "`";
    }
};

/// Lexing
std::vector<Token> lex(const std::string& input) {
    std::vector<Token> result;

    for (auto curr = std::begin(input); curr != std::end(input); curr++) {
        switch (*curr)
        {
        case '+': result.emplace_back(Token::plus, "+"); break;
        case '-': result.emplace_back(Token::minus, "-"); break;
        case '(': result.emplace_back(Token::lparen, "("); break;
        case ')': result.emplace_back(Token::rparen, ")"); break;
        default:
            auto first_non_digit = std::find_if(curr, std::end(input), [](auto c) {
                return !std::isdigit(c);
                });
            std::string integer = std::string(curr, first_non_digit);

            result.emplace_back(Token::integer, integer);
            curr = --first_non_digit;
        }
    }
    return result;
}

struct Element {
    virtual int eval() const = 0;
};

struct Integer : Element {
    int m_value;
    explicit Integer(const int v) : m_value(v) {}
    int eval() const {
        return m_value;
    }
};

struct BinaryOp : Element {
    enum Type {
        addition, subtraction
    }     m_type;
    std::shared_ptr<Element>                m_lhs, m_rhs;

    int eval() const {
        switch (m_type) {
        case Type::addition: return m_lhs->eval() + m_rhs->eval();
        case Type::subtraction: return m_lhs->eval() - m_rhs->eval();
        }
    }
};


/// Parsing
std::shared_ptr<Element> parse(const std::vector<Token> &tokens) {
    auto result = std::make_unique<BinaryOp>();

    for (auto curr_token = std::begin(tokens); curr_token != std::end(tokens); curr_token++) {
        switch (curr_token->m_type) {
        case Token::integer:
            if (!result->m_lhs) result->m_lhs = std::make_shared<Integer>(std::stoi(curr_token->m_text));
            else result->m_rhs = std::make_shared<Integer>(std::stoi(curr_token->m_text));
            break;
        case Token::plus: result->m_type = BinaryOp::addition; break;
        case Token::minus: result->m_type = BinaryOp::subtraction; break;
        case Token::lparen:
            auto rparen = std::find_if(curr_token, std::end(tokens), [](auto& token) {
                return token.m_type == Token::rparen;
                });
            std::vector<Token> subexpression(curr_token + 1, rparen);
            if (!result->m_lhs) result->m_lhs = parse(subexpression);
            else result->m_rhs = parse(subexpression);

            curr_token = rparen;
            break;
        }
    }

    return result;
}


int main(int argc, char const *argv[]) {
    std::string expression{ "(13-4)-(12+1)" };
    auto tokens = lex(expression);

    std::cout << "parsed expression" << std::endl;
    for (auto& t: tokens)
        std::cout << t << " ";

    std::cout << std::endl;

    auto parsed = parse(tokens);
    std::cout << expression << " = " << parsed->eval() << std::endl;

    return EXIT_SUCCESS;
}

