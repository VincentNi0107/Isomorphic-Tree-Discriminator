 
//
// This is example code from Chapter 7.7 "Recovering from errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"
#include <set>
#include <map>
/*
    Simple calculator

    Revision history:

        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
            (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from ss; output to cout.

    The grammar for input is:

    Statement:
        Expression
        Print
        Quit

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from ss through the Token_stream called ts.
*/

//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result
stringstream ss;
//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from ss
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);      // discard tokens up to an including a c
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // read characters from ss and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        return buffer;
    }

    char ch;
    ss >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
        return Token(ch); // let each character represent itself
    case '.':             // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        ss.putback(ch);// put digit back into the input stream
        double val;
        ss >> val;     // read a floating-point number
        return Token(number,val);
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // c represents the kind of a Token
{
    // first look in buffer:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now seach input:
    char ch = 0;
    while (ss>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

int jiecheng(int i){
    int ans=1;
    while(i>1){
        ans*=i;
        i--;
    }
    return ans;
}
// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            t= ts.get();
            if(t.kind=='!'){
                if(d<0){error("!: invalid factorial1");}
                int p=d;
                if(abs(p-d)<1e-9){
                    return jiecheng(p);
                }
                else error("!: invalid factorial2");
            }
            else{
                ts.putback(t);
                return d; 
            }
        }
    case number:
    {   double d=t.value;
        int p=d;
        t = ts.get();
        if(t.kind=='!'){
            if(abs(p-d)<1e-9){
                return jiecheng(p);
            }
            else error(": invalid factorial3");
        }
        else{
            ts.putback(t);
            return d; 
        }
    }
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("= primary expected");
    }
}


//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get(); // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(term());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);        // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate(string &input)
{
    while (ss)
    try {
        Token t = ts.get();
        // while (t.kind == print) t=ts.get();    // first discard all "prints"
        if (t.kind == print) return;        // quit
        ts.putback(t);
        double result=expression();
        string clean_input=input;
        while(clean_input[0]==' ')clean_input=clean_input.substr(1);
        clean_input.pop_back();
        while(clean_input.back()==' ')clean_input.pop_back();
        cout<<'\n'<<clean_input<<'='<<result;
    }
    catch (exception& e) {
        cout<<"error";
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
{
    string str1,str2;
    getline(cin,str1);
    getline(cin,str2);
    set <string> names;
    map <string,vector<string>> expresses;
    for (int i=0;i<str1.size();++i){
        if(str1[i]=='q')break;
        if(str1[i]=='['){
            string name;
            int j=i;
            bool space=false;
            while((++j)<str1.size()&&str1[j]!=']'){
                if(str1[j]!=' '||space){space=true;name+=str1[j];}
            }
            while(name.back()==' ')name.pop_back();
            string express;
            while((++j)<str1.size()&&str1[j]==' ');
            --j;
            while((++j)<str1.size()&&str1[j]!=';')express+=str1[j];
            express+=';';
            names.insert(name);
            bool exp_check=false;
            while((++j)<str1.size()&&str1[j]!='['&&str1[j]!='q'){
                if(str1[j]!=' ')exp_check=true;
            }
            i=j-1;
            if(!exp_check)expresses[name].push_back(express);
            continue;
        }
    }
    // auto it=names.begin();
    // while(it!=names.end()){
    //     cout<<'['<<*it<<']';
    //     cout<<expresses[*it].size()<<'\n';
    //     sort(expresses[*it].begin(),expresses[*it].end());
    //     for(int i=0;i<expresses[*it].size();++i){
    //         cout<<expresses[*it][i]<<'\n';
    //     }
    //     ++it;
    // }
    // return 0;
    if(str2==""){
        auto it=names.begin();
        while(it!=names.end()){
            cout<<'['<<*it<<']';
            sort(expresses[*it].begin(),expresses[*it].end());
            for(int i=0;i<expresses[*it].size();++i){
                ss<<expresses[*it][i];
                calculate(expresses[*it][i]);
                ss.clear();
            }
            ++it;
            if(it!=names.end())cout<<'\n';
        }
    }
    else{   
        while(str2[0]==' ')str2=str2.substr(1);
        cout<<'['<<str2<<']';
        sort(expresses[str2].begin(),expresses[str2].end());
        for(int i=0;i<expresses[str2].size();++i){
            ss<<expresses[str2][i];
            calculate(expresses[str2][i]);
        }

    }
    // if(getline(cin,str2))cout<<str2;

    return 0;
}


//------------------------------------------------------------------------------
// [chen  ](6!+9!)/((10!+2!)*1.2)-(2*(729/3/3/3/3/3)!)!/(2*5)! ; [ch en] ((6!+9!)/((10!+2!)*1.2)+(2*(729/3/3/3/3/3)!)!/(2*5)!)!; [     sh  e n ] ((6!+9!)/((10!+2!)*1.2)+(2*(729/3/3/3/3/3)!)!/(2*5)!)! (6!+9!)/((10!+2!)*1.2)-(2*(729/3/3/3/3/3)!)!/(2*5)!