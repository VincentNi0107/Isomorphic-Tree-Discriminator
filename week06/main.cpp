# include "std_lib_facilities.h"
# include <stack>
# include <queue>
string AHU(const string &str)
{   string leaf="10";
    if (str.length()==2) return leaf;


    int count = 1,start=1,str_len=0;
    priority_queue < string , vector < string >, greater < string > > q;
    string s1_left, s1_right, s2_left, s2_right;

    //取s1的左右字符串
    int s1_p = 1; //当前位置(()(()))
    while (count != 0)
    {
        if (str[s1_p] == '1'){
            count++;
        }            
        else{
            count--;
            if(count==1){
                string sub_string=str.substr(start,str_len+1);
                q.push(AHU(sub_string));
                start=s1_p+1;
                str_len=-1;
            }
        }
        str_len++;    
        s1_p++;
    }
    string result;
    while (q.size()>0)
    {
        result=result+q.top();q.pop();
    }
    return result;
    

}
bool check(const string &str){
    stack <int> tree;
    for(int i=0;i<str.length();++i){
        if(str[i]=='1'){
            tree.push(1);
        }
        else if (str[i]=='0')
        {   
            if(tree.empty()){
                return false;
            }
            else{
                tree.pop();
                if(tree.empty()&&i!=str.length()-1){
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
    if(tree.empty()) return true;
    return false;
}
int main() {
    string str1,str2;
    getline(cin, str1);
    getline(cin, str2);
    cout<<str1.length()+str2.length()+1<<":";
    string out;
    if(!check(str1)){
        out=out+" "+str1;
        
    }
    if(!check(str2)){
        out=out+" "+str2;
    }
    if(check(str1)&&check(str2)){
        if(AHU("1"+str1+"0")==AHU("1"+str2+"0")){
            out=str1+" and "+str2+" are isomorphic";
        }
        else{
            out=str1+" and "+str2+" are non-isomorphic";
        }
    }
    else{
        out="Invalid tree(s):"+out;
    }
    cout<<out.length()<<"\n"<<out;
    return 0;  
}