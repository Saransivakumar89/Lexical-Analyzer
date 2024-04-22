#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

class Lex
{
public:
    bool Operator(char token)
    {
		 return (token == '+' || token == '-' || token == '*' || token == '/' || token == '>' || token == '<' || token == '=' || token == '(' || token == ')' || token == '{' || token == '}' || token == ';' || token == ',' || token == '[' || token == ']' || token == '&' || token == '%' || token == '!' || token == '^' || token == '~');
    }

    bool Keyword(string str)
    {
        const vector<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

        for (int i = 0; i < keywords.size(); i++)
        {
            if (str == keywords[i])
            {
                return true;
            }
        }
        return false;
    }

    bool Identifier(string str)
    {
        const vector<string> identifiers = {"main", "printf", "scanf"};
        for (int i = 0; i < identifiers.size(); i++)
        {
            if (str == identifiers[i])
            {
                return true;
            }
        }
        return false;
    }

    string readFile(string filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Error : Unable to Open -> " << filename << endl;
            return ""; 
        }

        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    bool isComment(string line)
    {
        return line.substr(0, 2) == "//";
    }

    bool isCharacterLiteral(string str)
    {
        return str.size() == 3 && str[0] == '\'' && str[2] == '\'';
    }

    

    void tokenizeAndClassify(string content)
    {
        stringstream ss(content);
        string line;

        while (getline(ss, line))
        {
            stringstream lineStream(line);
            string word;

            while (lineStream >> word)
            {
                if (Operator(word[0]))
                {
                    cout << word << " -> Operator" << endl;
                }
                else if (Keyword(word))
                {
                    cout << word << " -> Keyword" << endl;
                }
                else if (Identifier(word))
                {
                    cout << word << " -> Identifier" << endl;
                }
                else if (isComment(word))
                {
                    cout << word << " -> Comment" << endl;
                }
                else if (isCharacterLiteral(word))
                {
                    cout << word << " -> Character literal" << endl;
                }
            
                else
                {
                    bool isIntegerLiteral = true;
                    for (char c : word)
                    {
                        if (!isdigit(c))
                        {
                            isIntegerLiteral = false;
                            break;
                        }
                    }
                    if (isIntegerLiteral)
                    {
                        cout << word << " -> Integer literal" << endl;
                    }
                    else
                    {
                        cout << word << " -> Other" << endl;
                    }
                }
            }
        }
    }
};

int main()
{
    Lex lex;
    string filename = "sample.cpp";
    string content = lex.readFile(filename);
    lex.tokenizeAndClassify(content);
    return 0;
}



