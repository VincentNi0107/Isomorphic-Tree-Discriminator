#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
# include "std_lib_facilities.h"
class Polynomial{
        friend pair <Polynomial, Polynomial> operator / (const Polynomial &a, const Polynomial &b);
    private:
        vector < pair < int, double > > p;
        bool errorflag;
    public:
        Polynomial();
        Polynomial(const Polynomial& rhs);
        Polynomial(const string &str);
        bool output(double p,string &out);
        bool iferr();
        string prt();
        void clean();
        void add(int a, double b);
        bool ifzero();    
};

#endif