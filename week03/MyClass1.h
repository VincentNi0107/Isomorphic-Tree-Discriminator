#include "std_lib_facilities.h"
#include "std_lib_facilities.h"
#ifndef MYCLASS1_H_
#define MYCLASS1_H_

class MyClass1{
        
    private:
        vector <string> legal;
        vector <string> illegal; 
        vector < vector <double> > A;
        vector < double > B;
        vector <pair<string,double>> result;
        vector <string> name;
        vector <vector <pair<int,double>>> store;
        bool checkEq(double x, double y, double eps);
        string out_double(double all);
    public:
        MyClass1();
        void add(const vector < pair <string, double> > &_vec);
        void gauss();
        pair < vector <double>, int > Gauss_Algorithm(const vector < vector <double> > &a, const vector <double> &b);
        void print_result();
};

#endif