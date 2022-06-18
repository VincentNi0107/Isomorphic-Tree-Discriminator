 
//
// This is example code from Chapter 7.7 "Recovering from errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"

/*
    Simple calculator

    Revision history:

        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
            (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from cin; output to cout.

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


        Input comes from cin through the Token_stream called ts.
*/

//------------------------------------------------------------------------------
string input;
string output;
int curser=0;
const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

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
    Token_stream();   // make a Token_stream that reads from cin
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

Token Token_stream::get() // read characters from cin and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        return buffer;
    }

    char ch;
    ch=input[curser];          // note that >> skips whitespace (space, newline, tab, etc.)
    if(ch==' '||ch=='\n'){
        curser++;
        ch=input[curser];
        }
    curser++;
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
        {return Token(ch);} // let each character represent itself
    case '.':             // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        curser--;// put digit back into the input stream
        double cur = 0, base = 1.0;
        while(input[curser]<='9'&&input[curser]>='0'||input[curser]=='.'){
            if(input[curser]=='.'){
                base=0.1;
                curser++;
            }
            else
            {
                double ps=input[curser]-'0';     // read a floating-point number
                curser++;
                if(base == 1.0) cur = cur * 10 + ps;
                else {
                cur = cur + base * ps;
                base = base * 0.1;
                }
            }
        }
        return Token(number,cur);
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
    while (curser<input.length()){
        curser++;
        if (input[curser]==c) return;
        
    }
        
        
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
                if(d<0){error("= !: invalid factorial");}
                int p=d;
                if(abs(p-d)<1e-9){
                    return jiecheng(p);
                }
                else error("= !: invalid factorial");
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
            else error("= !: invalid factorial");
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

void calculate()
{   
    while (curser<input.length())
      try {
        output+=prompt;
        Token t = ts.get();
        while (t.kind == print) t=ts.get();    // first discard all "prints"
        if (t.kind == quit) return;        // quit
        ts.putback(t);
        double expr=expression();
        int exp_int=expr;
        if(abs(expr-exp_int)<1e-9){
            output=output+result+to_string(exp_int)+"\n";
        }
        else{
            string tmp=to_string(expr);
            string out_double;
            int k=0;
            if(tmp[0]=='-'){
                k++;
                out_double+=tmp[0];
            }
            if(tmp[k]=='0'){
                out_double=tmp;
            }
            else{
                for(int i=k;i<6+k;++i){
                    out_double+=tmp[i];
                }
                if(tmp[6+k]>'4'){
                    // char a=tmp[6]+1;
                    out_double+=(tmp[6+k]+1);
                }
                else{
                    out_double+=tmp[6+k];
                }
                
            }
            output=output+result+out_double+"\n";
        }
    }
    catch (exception& e) {
        output=output+e.what()+"\n";
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
try {
    char ch;
    while((ch=cin.get())!=EOF)input+=ch;
    cout<<input.length()<<":";
    calculate();
    cout<<output.length()<<"\n"<<output;
    keep_window_open();    // cope with Windows console mode
    return 0;
}
catch (runtime_error& e) {
    cout << e.what() << endl;
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cout << "exception \n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------
