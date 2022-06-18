# include "std_lib_facilities.h"
# include <queue>
# include <map>

int main() {
    string str;
    getline(cin, str);
    vector <pair<string,int>> word_count;
    for(int i=0;i<str.length();++i){
        int j;
        string word(1,str[i]);
        for(j=0;j<word_count.size();++j){
            if(word_count[j].first==word){
                word_count[j].second++;
                break;
            }
        }
        if(j==word_count.size()){
            word_count.push_back(make_pair(word,1));
        }
    }
    priority_queue < pair <int, string> , vector < pair <int, string> >, greater < pair <int, string> > > q;
    map <string,string> code;
    for(int i=0;i<word_count.size();++i){
        q.push(make_pair(word_count[i].second,word_count[i].first));
        code[word_count[i].first]="";
    }
    // map<string, string>::iterator  iter;
    // for (iter = code.begin(); iter != code.end(); ++iter)
    // {
    //     cout<<iter->first<<":"<<iter->second<<"\n";
    // }
    while (q.size()>1)
    {
        pair<int,string> left=q.top();q.pop();
        pair<int,string> right=q.top();q.pop();
        q.push(make_pair(left.first+right.first,left.second+right.second));
        for(int i=0;i<left.second.size();++i){
            string tmp(1,left.second[i]);
            code[tmp]="0"+code[tmp];
        }
        for(int i=0;i<right.second.size();++i){
            string tmp(1,right.second[i]);
            code[tmp]="1"+code[tmp];
        }
    }
    string out;
    int sentence_len=0;
    for(int i=0;i<word_count.size();++i){
        sentence_len+=code[word_count[i].first].length()*word_count[i].second;
    }
    out=out+to_string(sentence_len);
    map<string, string>::iterator  iter;
    for (iter = code.begin(); iter != code.end(); ++iter)
    {
        out=out+"\n"+iter->first+" "+iter->second;
    }
    cout<<str.length()<<":"<<out.length()<<"\n"<<out;
    return 0;  
}