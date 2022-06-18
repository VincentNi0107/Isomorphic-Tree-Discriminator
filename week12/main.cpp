#include "std_lib_facilities.h"

double onedouble(const string &str) {
    double x=0;
    bool f = 0; x = 0;
    int beg;
    if(str[0] == '-') f = 1;
    beg = f;
    double bse = 1.0;
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          x = x + bse * (str[beg] - '0');
          bse *= 0.1;
        } else x = x * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == f) throw 233;
    if(beg != str.size()) throw 233;
    if(f) x = -x;
    return x;
  }
  void twodouble(const string &str, double &x, double &y) {
    bool f = 0; x = 0; y = 0;
    int beg;
    if(str[0] == '-') f = 1;
    beg = f;
    double bse = 1.0;
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          x = x + bse * (str[beg] - '0');
          bse *= 0.1;
        } else x = x * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == f) throw 233;
    if(f) x = -x;
    
    if(str[beg] != ' ') throw 233;
    ++ beg; f = 0; bse = 1.0;
    if(str[beg] == '-') f = 1, ++ beg;
    int lst = beg;
    
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          y = y + bse * (str[beg] - '0');
          bse *= 0.1;
        } else y = y * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == lst) throw 233;
    if(beg != str.size()) throw 233;
    if(f) y = -y;
  }
  inline bool checkEq(double x, double y, double eps) {
    return abs(x - y) < eps;
  }
  inline bool output(double p) {
	if(p > 0) p += 0.000001;
	else p -= 0.000001;
    string out = ""; 
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
    cout << out;
    return true;
  }
//定义main函数
int main()
{
    /********** Begin **********/
    bool exercisel = false;
   	if (exercisel){
    //第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
   		string str;
        getline(cin, str);
        double predict;
        try {
            predict=onedouble(str);
        } catch(...) {
            cout << "error";
            return 0;
        }
        pair <double,double> x_y;
        vector <pair <double,double>> data;
        while(getline(cin, str)) {
            try {
                twodouble(str, x_y.first, x_y.second);
            } 
            catch(...) {
                cout << "error";
                return 0;
            }
             data.push_back(x_y);
        }

        sort(data.begin(), data.end());
  
        for (int i = 0; i < data.size() - 1; ++ i) 
            if(checkEq(data[i + 1].first - data[i].first, data[1].first - data[0].first, 1e-8) == false) {
                cout << "error";
                return 0;
            }

        vector < vector <double> > tab;
        int n = data.size();
        tab.resize(n);
        for (int i = 0; i < n; ++ i) tab[i].resize(n);
        for (int i = 0; i < n; ++ i) tab[0][i] = data[i].second;
        for (int i = 1; i < n; ++ i)
            for (int j = i; j < n; ++ j)
                tab[i][j] = (tab[i - 1][j] - tab[i - 1][j - 1]) / (data[j].first - data[j - i].first);

        vector <double> t;
        vector <double> xx;
        vector <double> poly;
        xx.resize(n); 
        poly.resize(n); 
        t.resize(n);
        poly[0] = tab[0][0]; 
        xx[0] = 1.0;
        for (int i = 1; i < n; ++ i) xx[i] = poly[i] = 0; 
        for (int i = 1; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) t[j] = 0;
            for (int j = 1; j < n; ++ j) t[j] = xx[j - 1];
            for (int j = 0; j < n; ++ j) t[j] = t[j] - data[i - 1].first * xx[j];
            for (int j = 0; j < n; ++ j) xx[j] = t[j];
            for (int j = 0; j < n; ++ j) poly[j] += tab[i][i] * xx[j]; 
        }
        int times = n - 1;;
        double ans = 0.0;
        for (int i = 0; i <= times; ++ i) {
            double t = tab[i][i];
            for (int j = 0; j < i; ++ j) t = t * (predict - data[j].first);
            ans += t;
        }
        if(checkEq(ans, 0.0, 1e-5)) cout << "0.0000";
        else printf("%.4lf", ans - 0.00001);

    } else{
   	//第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
        string str;
        getline(cin, str);
        double predict;
        try {
            predict=onedouble(str);
        } 
        catch(...) {
            cout << "error\nerror\nerror";
            return 0;
        }
        pair <double,double> x_y;
        vector <pair <double,double>> data;
        while(getline(cin, str)) {
            try {
                twodouble(str, x_y.first, x_y.second);
            } 
            catch(...) {
                cout << "error\nerror\nerror";
                return 0;
            }
             data.push_back(x_y);
        }
        if(data.size() < 2) { 
            cout << "error\nerror\nerror";
            return 0;
        }
        int n = data.size();
        double r,A,B;
        try {
        double xx = 0, x = 0, xy = 0, y = 0, ru = 0, rd1 = 0, rd2 = 0, rd;
        for (int i = 0; i < n; ++ i) {
            xx += data[i].first * data[i].first;
            x += data[i].first;
            xy += data[i].first * data[i].second;
            y += data[i].second;
        }
            double xbar = x / n, ybar = y / n;
            for (int i = 0; i < n; ++ i) {
                ru += (data[i].first - xbar) * (data[i].second - ybar);
                rd1 += (data[i].first - xbar) * (data[i].first - xbar);
                rd2 += (data[i].second - ybar) * (data[i].second - ybar);
            }
            rd = sqrt(rd1 * rd2);
            r = ru / rd;
            if(abs(r) < 0.75) throw "error";
            if(checkEq(xx * n - x * x, 0.0, 1e-8)) throw "error";
            A = (xy * n - x * y) / (xx * n - x * x);
            B = (xx * y - x * xy) / (xx * n - x * x);
        }
        catch(...) {
            if(output(r) == false) cout << "0.0000";
            cout << "\nerror\nerror";
            return 0;
        }
        double ans = A * predict + B;
        if(output(r) == false) cout << "0.0000";
        cout << endl;
        cout << "y=";
        if(checkEq(A, 0.0, 1e-8) == false) {
            output(A);
            cout << "*x";
            if(checkEq(B, 0.0, 1e-8) == false) {
                if(B > 0) cout << '+';
                output(B);
            }
        } else {
            if(checkEq(B, 0.0, 1e-8) == false) output(B);
            else std :: cout << "0.0000";
        }
            cout << endl;
            if(output(ans) == false) cout << "0.0000";
    }
    
	/********** End **********/
  	return 0;
}

