#include "std_lib_facilities.h"
#include "MyClass1.h"
MyClass1::MyClass1(){
    vector < pair <string, double> > tem;
    string name="b";
    int right;
    string str;
    while(getline(cin, str)) { 
        if(str=="")break;
        tem.clear();
        bool errorflag = 0;
        double cur = 0, base = 1.0;
        bool flag = (str[0] == '-');
        int r = 0;
        bool eq = 0;
        bool b=true;
        for (int i = flag; i < str.length(); ++ i) {
          if ('0' <= str[i] && str[i] <= '9') {
            int ps = (str[i] - '0');
            if(base == 1.0) cur = cur * 10 + ps;
            else {
              cur = cur + base * ps;
              base = base * 0.1;
            }
          } else if(str[i] == '.') {
            if(base != 1.0) errorflag = 1; 
            base = 0.1;
          } else if(str[i] == '*') {
            if(i==0||(i+1)==str.length()||!isdigit(str[i-1])||'a'>str[i+1]||str[i+1]>'z') errorflag=1;
          }else if('a'<=str[i] && str[i]<='z' ) {
            if(i == 0 || str[i-1] == '+' || str[i-1] == '-') cur = 1.0;
            if(i + 1 < str.length()) {
              int j = i + 1;
              if(!isdigit(str[j])) errorflag = 1;
              else {
                r=str[j]-'0';
                while(j + 1 < str.length() && '0' <= str[j+1] && str[j+1] <= '9') {
                  ++ j;
                  r = r * 10 + (str[j] - '0');
                }
                if(j + 1 < str.length() && str[j+1] != '+' && str[j+1] != '-' && str[j+1] != '=') errorflag = 1;
                if(r > 100) errorflag = 1;
                name=str[i]+to_string(r);
                b=false;
                i = j;
              } 
            } else errorflag = 1;
          } else if(str[i] == '+') {
            if(i && !isdigit(str[i-1])) errorflag = 1;
            else {
              if(flag) cur = -cur;
              if(b&&eq){
                name='b';
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
                  }
              else if(!b&&!eq){
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
              } 
                else errorflag=1;
            }
          } else if(str[i] == '-') {
            if(i && str[i-1] == '=') flag = 1;
            else {
              if(i && !isdigit(str[i-1])) errorflag = 1;
              else {
                if(flag) cur = -cur;
                if(b&&eq){
                name='b';
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
                  }
              else if(!b&&!eq){
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
              } 
                else errorflag=1;
              }
              flag=1;
            } 
          } else if(str[i] == '=') {
            if(i==0||!isdigit(str[i-1])||i+1==str.length()) errorflag = 1;
            else {
              if(flag) cur = -cur;
              if(b&&eq){
                name='b';
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
                  }
              else if(!b&&!eq){
                tem.push_back(make_pair(name, cur));
                flag = 0; cur = 0; base = 1.0; r = 0;b=true;
              } 
                else errorflag=1;
            }
            eq = 1;
          } else errorflag = 1;
          if(errorflag) break;
        }
        if(flag) cur = -cur;
        if(b&&eq){
            name='b';
            tem.push_back(make_pair(name, cur));
            flag = 0; cur = 0; base = 1.0; r = 0;b=true;
                }
            else if(!b&&!eq){
            tem.push_back(make_pair(name, cur));
            flag = 0; cur = 0; base = 1.0; r = 0;b=true;
            } 
            else errorflag=1;
        for (int i=0;i<tem.size();++i){
            for (int j=0;j<i;++j){
                if(tem[i].first==tem[j].first) errorflag=1;
            }
        }
        if(errorflag) {
            illegal.push_back(str);
            }
        else{
            legal.push_back(str);
            add(tem);
        }
        // cout<<tem.size()<<'\n';
        // for (int i=0;i<tem.size();++i){
        //     cout<<tem[i].first<<" "<<tem[i].second<<'\n';
        // }
} 
}
void MyClass1::add(const vector < pair <string, double> > &vec){
    vector <pair<int,double>> line;
    for(int i=0;i<vec.size();++i){
        int j=0;
        if(vec[i].first =="b"){
            B.push_back(vec[i].second);
            continue;
        }
        for(j=0;j<name.size();++j){
            if(vec[i].first==name[j]){
                line.push_back(make_pair(j,vec[i].second));
                break;
            }
        }
        if(j==name.size()){
            name.push_back(vec[i].first);
            line.push_back(make_pair(j,vec[i].second));
        }
    }
    store.push_back(line);
    // for(int i=0;i<line.size();++i){
    //     cout<<line[i].first<<" "<<line[i].second<<"\n";
    // }
}
bool MyClass1::checkEq(double x, double y, double eps) {
    return abs(x - y) < eps;
  }
pair < vector <double>, int > MyClass1::Gauss_Algorithm(const vector < vector <double> > &a, const vector <double> &b){
  vector < vector <double> > A(a);
  vector <double> B(b);
  vector <double> res;
  int m=name.size();
  int n=B.size();
  bool flag = 0;
  res.resize(m);
  for (int i = 0; i < m; ++ i) {
    if(i >= n) break;
    int pos = -1;
    for (int j = i; j < n; ++ j)
      if(! checkEq(A[j][i], 0.0, 1e-7)) { pos = j; break; }
    if(pos == -1) {
      flag = 1;
      continue;
    }
    
    for (int j = 0; j < m; ++ j) swap(A[i][j], A[pos][j]);
    swap(B[i], B[pos]);
    
    for (int j = i + 1; j < n; ++ j) {
      double c = A[j][i] / A[i][i];
      for (int k = 0; k < m; ++ k) A[j][k] = A[j][k] - c * A[i][k];
      B[j] = B[j] - c * B[i];
    }
  }
  
  for (int i = 0; i < n; ++ i) {
    bool no = 1;
    for (int j = 0; j < m; ++ j)
      no &= (checkEq(A[i][j], 0.0, 1e-7));
    no &= (checkEq(B[i], 0.0, 1e-7) ^ 1);
    if(no) error("error1\n");
  }
  
  if(flag || m > n) error("error2\n");
  
  if(m < n) {
    for (int i = m; i < n; ++ i) {
      for (int j = 0; j < m; ++ j)
        if(! checkEq(A[i][j], 0.0, 1e-7)) error("error1\n");
      if(! checkEq(B[i], 0.0, 1e-7)) error("error1\n");
    }
  }
  
  for (int i = m - 1; ~i; -- i) {
    res[i] = B[i] / A[i][i];
    for (int j = 0; j < i; ++ j) 
      B[j] = B[j] - A[j][i] * res[i];
  }
  
  return make_pair(res, 0);
}
string MyClass1::out_double(double all) {
    string out;
    int point = all * 10000, n = all;
    if(point == 0) return "0.0000";
    if(all < 0) {
      n = -n; 
      point = -point;
      out = out + "-";
    }
    out = out + to_string(n) + ".";
    point -= n * 10000;
    if(point < 10) out = out + "000";
    else if(point < 100) out = out + "00";
    else if(point < 1000) out = out + "0";
    out = out + to_string(point);
    return out;}
void MyClass1::gauss(){
  vector <string> seq(name);
  sort(seq.begin(), seq.end());
  // for(int i=0;i<seq.size();++i){
  //   cout<<seq[i]<<" "<<name[i]<<"\n";
  // }
  
  int m=name.size();
  int n=B.size();
  int input_size=0;
  string output="Legal Equations:\n";
  
  for(int i=0;i<B.size();++i){
      vector <double> temp;
      for(int j=0;j<name.size();++j){
          temp.push_back(0);
      }
      for(int j=0;j<store[i].size();++j){
          temp[store[i][j].first]=store[i][j].second;
      }
      A.push_back(temp);
      temp.clear();}
      for(int i=0;i<legal.size();++i){
        output+=legal[i];
        output+='\n';
        input_size+=legal[i].length();
        input_size++;
    }
  // cout<<m<<" "<<n<<"\n";
  // for (int i=0;i<n;++i){
  //   for (int j=0;j<m;++j){
  //     cout<<A[i][j]<<" ";
  //   }
  //   cout<<B[i]<<"\n";
  // }
  try{
      pair < vector <double>, int > ans(Gauss_Algorithm(A, B));
      for (int i = 0; i < m; ++ i) {
      int j=0;
      for(j=0;j<m;++j){
        if(name[j]==seq[i])break;
      }
      output=output+seq[i]+":"+out_double(ans.first[j])+"\n";
    }
  }
  catch (exception& e) {
    output+=e.what();      // write error message
    }
  output+="Illegal Equations:";
  for(int i=0;i<illegal.size();++i){
        output=output+"\n"+illegal[i];
        input_size+=illegal[i].length();
        input_size++;
    }
  cout<<input_size-1<<":"<<output.length()<<"\n"<<output;
}
