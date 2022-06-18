# include "std_lib_facilities.h"
#include "Polynomial.h"

int main(){
    string str1;
    string str2;
    getline(cin, str1);
    getline(cin, str2);
    Polynomial ploy1(str1),ploy2(str2);
    if(ploy1.iferr()||ploy2.iferr()||ploy2.ifzero()){
        cout<<str1.length()+str2.length()+1<<":"<<"23\n";
        cout<<"error\nerror\nerror\nerror";
        return 0;
            }
    
    string out1=ploy1.prt();
    // string out2=ploy2.prt();
    // pair <Polynomial, Polynomial> result=ploy1/ploy2;
    // string out3=result.first.prt();
    // string out4=result.second.prt();
    // cout<<str1.length()+str2.length()+1<<":"<<out1.length()+out2.length()+out3.length()+out4.length()+3<<"\n";
    // cout<<out1<<"\n"<<out2<<"\n"<<out3<<"\n"<<out4;
    return 0;
}