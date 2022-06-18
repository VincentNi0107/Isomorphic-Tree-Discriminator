# include "std_lib_facilities.h"
# include <vector>
#include <cmath>
#include <algorithm>
void method1(const string &str){
        int num=0;
        for (int i=0;i<str.length();++i){
            num=num*10+str[i]-'0';
        }
        string out;
        int cnt=0;
        for(int i=1;i<num;++i){
            if(num%i==0){
                string a=to_string(i);
                out=out+to_string(i)+" ";
                cnt++;
            }
        }
        out=out+to_string(num);
        cnt++;
        string count=to_string(cnt);
        cout<<2*(out.length()+count.length()+1)+1<<"\n"<<cnt<<" "<<out<<"\n";
        return ;
}
void find_factor(int num,vector<int> &fact,vector<int> &pow_fac){
    int k=2;
    while(num>1){
        if(num%k==0){
            int pow_num=0;
            fact.push_back(k);
            while(num%k==0){
                num=num/k;
                pow_num++;
            }
            pow_fac.push_back(pow_num);
        }
        k++;
    }
    return;
}
void mul_factor(vector<int> &fact,vector<int> &pow_fac,vector<int> &all){

    int num_of_fact=1;
    for(int i=0;i<pow_fac.size();++i){
        num_of_fact*=(pow_fac[i]+1);
    }
    cout<<num_of_fact;
    if(num_of_fact==1){
        all.push_back(1);
        return;
    }
    for (int j=0;j<=pow_fac[0];++j){
            all.push_back(pow(fact[0],j));
        }
    for(int i=1;i<pow_fac.size();++i){
        int pre_size=all.size();
        for(int j=0;j<pre_size;j++){
            for (int k=1;k<=pow_fac[i];k++){
                all.push_back(all[j]*pow(fact[i],k));
            }
        }
    }   
    return;
}
void method2(const string str){
    int num=0;
    for (int i=0;i<str.length();++i){
        num=num*10+str[i]-'0';
    }
    vector<int> prime_factor,fac_pow,all_factor;

    find_factor(num,prime_factor,fac_pow);
    mul_factor(prime_factor,fac_pow,all_factor);
    sort(all_factor.begin(),all_factor.end());
    for(int i=0;i<all_factor.size();i++){
        cout<<" "<<all_factor[i];
    }
    return;
        
}

int main(){
    string str;          
    getline(cin,str);
    cout<<str.length()<<":";
    method1(str);
    method2(str);
    return 0;
}