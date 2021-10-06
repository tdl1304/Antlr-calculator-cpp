#include <iostream>
#include "antlr4-runtime/ExprBaseListener.h"
#include "antlr4-runtime/ExprLexer.h"
#include "antlr4-runtime/ExprParser.h"

#include <stack>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include<cmath>
#include<climits>

using namespace std;
using namespace antlr4;
using namespace antlr4::tree;

bool TryParse(const string &symbol) {
    bool isNumber = false;
    for (char i : symbol) {
        isNumber = isdigit(i) != 0;
    }
    return isNumber;
}

int Priority(const string &c) {
    if (c == "^") {
        return 3;
    }
    if (c == "*" || c == "/") {
        return 2;
    }
    if (c == "+" || c == "-") {
        return 1;
    } else {
        return 0;
    }
}

bool isOperator(const string &c) {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
}

string sya(string infix) {
    istringstream iss(infix);
    vector<string> tokens;//store the tokens here
    while (iss) {
        string temp;
        iss >> temp;
        tokens.push_back(temp);
    }
    vector<string> outputList;//output vector
    stack<string> s;//main stack

    //operator: +, -, *, /, ^, ()
    //operands: 1234567890
    for (const auto &token : tokens)  //read from right to left
    {
        if (TryParse(token)) {
            outputList.push_back(token);
        }
        if (token == "(") {
            s.push(token);
        }
        if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                outputList.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        if (isOperator(token)) {
            while (!s.empty() && Priority(s.top()) >= Priority(token)) {
                outputList.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }
    //pop any remaining operators from the stack and insert to outputlist
    while (!s.empty()) {
        outputList.push_back(s.top());
        s.pop();
    }
    string res;
    for (const auto &i : outputList) {
        res += i + " ";
    }
    return res;
}

double scanNum(string token) {
    double value;
    value = atof(token.c_str());
    return value;//return float from character
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';//character is an operator
    // false if not an operator
}

double operation(double a, double b, char op) {
    //Perform operation
    if (op == '+')
        return b + a;
    else if (op == '-')
        return b - a;
    else if (op == '*')
        return b * a;
    else if (op == '/')
        return b / a;
    else if (op == '^')
        return pow(b, a); //find b^a
    else
        return INT_MIN; //return negative infinity
}

double postfixEval(string postfix) {
    double a, b;
    stack<double> stk;
    postfix.append(" ");
    string delimiter = " ";
    size_t pos = 0;
    string token;

    //loop through every token in postfix
    while ((pos = postfix.find(delimiter)) != std::string::npos) {
        token = postfix.substr(0, pos);
        if (!token.empty()) {
            if (isOperator(token)) {
                a = stk.top();
                stk.pop();
                b = stk.top();
                stk.pop();
                stk.push(operation(a, b, token[0]));
            } else {
                stk.push(scanNum(token));
            }
        }
        postfix.erase(0, pos + delimiter.length());
    }

    return stk.top();
}

class EvalListener : public ExprBaseListener {
    map<string, string> vars;
    stack<string> varKeys;
    string buf;

public:

    // assign variables
    void enterAssn(ExprParser::AssnContext *ctx) override {
        vars.insert({ctx->ID()->getText(), ctx->num()->getText()});
        varKeys.push(ctx->ID()->getText());
    }

    void visitTerminal(antlr4::tree::TerminalNode *node) override {
        if (node->getText() == ";") {
            if (buf.find('=') == std::string::npos) { //only calculating expressions
                cout << postfixEval(sya(formatExpr(buf))) << endl;
            }
            buf = "";
        } else {
            buf += node->getText() + " ";
        }
    }


    string formatExpr(string expression) {
        //replace ID with NUM if there are IDs in expr
        if (!varKeys.empty()) {
            while (!varKeys.empty()) {
                string key = varKeys.top();
                int index = 0;
                do {
                    index = expression.find(key);
                    if (index == std::string::npos) break;
                    expression.replace(index, key.size(), "" + vars.at(key) + "");
                    index += key.size();
                } while (index < expression.size());
                varKeys.pop();
            }
        }
        // operator cleanup
        for (int i = 0; i < expression.size(); i++) {
            char c = expression[i];
            if (c == '-') {
                if (i == 0) { continue; }
                else if (expression[i - 2] == '+') {
                    expression.replace(i - 2, 2, "");
                }
            } else if (c == '+') {
                if (i == 0) {
                    expression.replace(i, 1, "");
                } else if (expression[i - 2] == '(') {
                    expression.replace(i, 2, "");
                }
            }
        }
        return expression;
    }
};


int main() {
    cout << "** Expression Eval with ANTLR Listener **" << endl;
    cout << "Please enter absolute path for input.txt file >";
    string s;
    cin >> s;
    string line;
    string input_string;
    ifstream stream(s);


    while (getline(stream, line)) {
        input_string += line;
    }
    stream.close();

    ANTLRInputStream input(input_string);
    ExprLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    ExprParser parser(&tokens);
    ParseTree *tree = parser.prog();

    //print tree
    //cout << tree->toStringTree(&parser) << endl;

    ParseTreeWalker walker;
    EvalListener listener;

    //go through tree
    walker.walk(&listener, tree);

    return 0;
}
