#include "std_lib_facilities.h"
#include "Polynomial.h"

Polynomial:: Polynomial(const string &str){
    errorflag = 0; p.clear();
    double cur = 0, base = 1.0;
    bool flag = (str[0] == '-');
    int r = 0;
    for (int i = flag; i < str.length(); ++ i) {
    if ('0' <= str[i] && str[i] <= '9') {
        int ps = (str[i] - '0');
        if(base == 1.0) cur = cur * 10 + ps;
        else {
        cur = cur + base * ps;
        base = base * 0.1;
        }
    } else if(str[i] == '.') {
        if(base != 1.0) {
        errorflag = 1;
        return ;
        }
        base = 0.1;
    } else if(str[i] == 'x') {
        if(i == 0 || str[i-1] == '+' || str[i-1] == '-') cur = 1.0;
        if(i + 1 < str.length() && str[i + 1] == '^') {
        int j = i + 1;
        if(j + 1 == str.length() || !isdigit(str[j + 1])) {
            errorflag = 1;
            return ;
        }
        while(j + 1 < str.length() && '0' <= str[j+1] && str[j+1] <= '9') {
            ++ j;
            r = r * 10 + (str[j] - '0');
        }
        if(j + 1 < str.length() && str[j+1] != '+' && str[j+1] != '-') {
            errorflag = 1;
            return ;
        }
        i = j;
        } else {
        if(i+1 < str.length() && str[i + 1] != '+' && str[i + 1] != '-') {
            errorflag = 1;
            return ;
        }
        r = 1;
        }
    } else if(str[i] == '+') {
        if(i && !isdigit(str[i-1]) && str[i-1] != 'x') {
        errorflag = 1;
        return ;
        }
        if(flag) cur = -cur;
        p.push_back(std :: make_pair(r, cur));
        flag = 0; cur = 0; base = 1.0; r = 0;
    } else if(str[i] == '-') {
        if(i && !isdigit(str[i-1]) && str[i-1] != 'x') {
        errorflag = 1;
        return ;
        }
        if(flag) cur = -cur;
        p.push_back(std :: make_pair(r, cur));
        flag = 1; cur = 0; base = 1.0; r = 0;
    } else errorflag = 1;
    }
    if(flag) cur = -cur;
    p.push_back(std :: make_pair(r, cur));
    sort(p.begin(), p.end());
    std :: vector < std :: pair < int, double > > tem;
    tem.clear();
    for (int i = 0; i < p.size(); ++ i) {
    int j = i; 
    double cur = p[i].second;
    while(j + 1 < p.size() && p[j + 1].first == p[i].first) {
        ++ j;
        cur += p[j].second;
    }
    i = j;
    if(abs(cur - 0.0) < 1e-9) continue;
    tem.push_back(std :: make_pair(p[i].first, cur));
    }
    p.clear();
    for (int i = 0; i < tem.size(); ++ i) p.push_back(tem[i]);
}
Polynomial::Polynomial(const Polynomial& rhs) {
      errorflag = rhs.errorflag;
      p.clear();
      for (int i = 0; i < rhs.p.size(); ++ i) p.push_back(rhs.p[i]);
    }
Polynomial::Polynomial() { errorflag = 0; p.clear(); }
bool Polynomial::output(double p,string &out) {
    int pc = p * 10000, z = p;
    if(pc == 0) return false;
    if(p < 0) {
      z = -z; pc = -pc;
      out = out + "-";
    }
    out = out + to_string(z) + ".";
    pc -= z * 10000;
    if(pc < 10) out = out + "000";
    else if(pc < 100) out = out + "00";
    else if(pc < 1000) out = out + "0";
    out = out + to_string(pc);
    return true;
  }
void Polynomial::clean() {
      sort(p.begin(), p.end());
      vector < pair < int, double > > tem;
      tem.clear();
      for (int i = 0; i < p.size(); ++ i) {
        int j = i; 
        double cur = p[i].second;
        while(j + 1 < p.size() && p[j + 1].first == p[i].first) {
          ++ j;
          cur += p[j].second;
        }
        i = j;
        if(abs(cur-0.0)<1e-9) continue;
        tem.push_back(make_pair(p[i].first, cur));
      }
      p.clear();
      for (int i = 0; i < tem.size(); ++ i) p.push_back(tem[i]);
    }
void Polynomial::add(int a, double b) {
      p.push_back(make_pair(a, b));
    }
bool Polynomial::iferr(){
    return errorflag;
}
bool Polynomial::ifzero(){
    return abs(p[0].second-0.0)<1e-9;
}
string Polynomial::prt() {
      bool start = 1;
      string out;
      for (int i = p.size() - 1; i>=0; -- i) {
        if(p[i].second > 0 && flag != 1) out.append("+");
        if(output(p[i].second,out) == true) {
          start = 0;
          if(p[i].first > 1) {
            out.append("x^");
            out.append(to_string(p[i].first));
            }
          else if(p[i].first == 1) out.append("x");
        }
      }
      if(start) out.append("0.0000");
      return out;
    }
pair <Polynomial, Polynomial> operator / (const Polynomial &a, const Polynomial &b) {
    Polynomial res(a), div;
    while(res.p.size() && res.p[res.p.size() - 1].first >= b.p[b.p.size() - 1].first) {
    int delta = res.p[res.p.size() - 1].first - b.p[b.p.size() - 1].first;
    double r = res.p[res.p.size() - 1].second / b.p[b.p.size() - 1].second;
    div.add(delta, r);
    for (int i = 0; i < b.p.size(); ++ i)
        res.add(b.p[i].first + delta, - r * b.p[i].second);
    res.clean();
    }
    sort(div.p.begin(), div.p.end());
    return make_pair(div, res);
} 
