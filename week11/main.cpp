# include "std_lib_facilities.h"
using namespace std;
vector <vector<int>> len;
vector <vector<int>> p;
string str;
int dp(int l,int r);
string prt(int l,int r);
int main(){
    int exercise = 3;
    if(exercise==1){
        int w,n;
        vector<int> weight;
        weight.resize(n);
        cin>>w>>n;
        int tmp;
        for(int i=0;i<n;++i){
            cin>>tmp;
            weight.push_back(tmp);
        }
        sort(weight.begin(),weight.end());
        if(weight.front()<=0){
            cout<<"error";
            return 0;
        }
        if(weight.back()>w){
            cout<<"out";
            return 0;
        }
        int ans=0;
        for(int i=n-1,j=0;i>=j;i--){
            if(i==j){
                ans++;
                break;
            }
            if(weight[i]+weight[j]<=w){
                ans++;
                j++;
            }
            else ans++;
        }
        cout<<ans;
    }
    else if (exercise==2)
    {
        int n;
        cin>>n;
        if(n<1||n>100000){
            cout<<"error";
            return 0;
        }
        vector<int> arr;
        arr.resize(n);
        int num=-1,tmp;
        bool flag=false;
        while (cin>>tmp)
        {
            num++;
            if(num>=n||tmp>1000||tmp<-1000){
                cout<<"error";
                return 0;
            }
            if(tmp>0)flag=true;
            arr[num]=tmp;
        }
        cout<<num;
        if(num!=n-1){
            cout<<"error";
            return 0;
        }
        int sum=0,maxSum=0,begin=0,left,right;
        if(flag){
            for(int i=0;i<n;++i){
                sum+=arr[i];
                if(sum<0){
                    sum=0;
                    begin=i+1;
                }
                if(sum>maxSum){
                    maxSum=sum;
                    left=begin;
                    right=i;
                }
            }
        }
        else{
            maxSum=-1001;
            for(int i=0;i<n;++i){
                if(arr[i]>maxSum){
                    maxSum=arr[i];
                    left=right=i;
                }
            }
        }
        cout<<maxSum<<" "<<left+1<<" "<<right+1;
    }
    else{
        getline(cin,str);
        int n=str.size();
        len.resize(n);
        p.resize(n);
        for(int i=0;i<n;++i){
            len[i].resize(n);
            p[i].resize(n);
        }
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                len[i][j]=-1;
                p[i][j]=0;
            }
        }
        dp(0,n-1);
        cout<<prt(0,n-1);
    }
    
    return 0;
}

int dp(int l,int r){
    if(l>=r) return 0;
    if(len[l][r]!=-1) return len[l][r];
    if(str[l]==str[r]){
        len[l][r]=dp(l+1,r-1)+2;
        p[l][r]=1;
        return len[l][r];
    }
    if(str[l]!=str[r]){
        len[l][r]=dp(l,r-1)>dp(l+1,r)?dp(l,r-1):dp(l+1,r);
        p[l][r]=dp(l,r-1)>dp(l+1,r)?2:3;
        return len[l][r];
    }
}
string prt(int l,int r){
    if(l>=r) return "";
    if(p[l][r]==1) return str[l]+prt(l+1,r-1)+str[r];
    if(p[l][r]==2) return prt(l,r-1);
    if(p[l][r]==3) return prt(l+1,r);
}