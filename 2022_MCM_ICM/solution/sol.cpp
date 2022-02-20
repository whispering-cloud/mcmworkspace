#include <cstdio>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#define ms(arr,val) memset(arr,val,sizeof(arr))
using namespace std;

struct status{
	short dr,ds,dv;
	short power;
};

const double c_r = 0.003;
const int m = 80;
const double g = 9.8;
const double eta = 0.95;
const double rho = 1.2;
const double c_wA = 0.31;
const int R = 1000;

double h[10000];
int cnt;
double v_w[10000];

status ansr;
short ansp[1460];

int M,E,CP,LT;
status *tmmp;
static short dp[1460][1002][301];
vector<status> pre[1002][301];
/*
tuple<int, int, int> delta(int s, int p, int v) // r,s,v
{
		double theta = atan2((h[s + 1] - h[s]), 0.01);
		double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
		double a = (-f * v / 10 + p) / (v / 10 * m);
		return make_tuple(CP - double(p) / E, (2 * v + int(10 * a)) / 2, (int)(10 * a));
}*/

status delta(int s,int p,int v){
	status res;
	double theta = atan2((h[s + 1] - h[s]) , 0.01);
	double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
	double a = (-f * v / 10 + p) / (v / 10 * m + 0.01);
	res.dv = int(100*a);
	res.ds = (2*v+int(100*a))/2;
	res.dr = 10 * (CP - double(p) / E);
	return res;
}

int solve(){
	cout<<1;
	status tmpt,del;
	for (int i=0;i<1460;i++){
		//cout<<i<<endl;
		for (int j=1000;j>=0;j--){
			for (int k=0;k<=250;k++){
				if(dp[i][j][k]>=cnt) {
					//cout<<dp[i][j][k];
					ansr.ds=i;
					ansr.dv=k;
					ansr.dr=j;
					return i;
				}
				if(dp[i][j][k]==-1) continue;
				int pmax=M*j/1000-LT*i;
				for (int p=10;p<=pmax;p+=10){
					del = delta(dp[i][j][k],p,k);
					int tmpr=max(0,min(1000,j+del.dr));
					if(dp[i+1][tmpr][k+del.dv]<dp[i][j][k]+del.ds){
						tmpt.ds=i;//this ds = time
						tmpt.dr=j;
						tmpt.dv=k;
						tmpt.power=p;
						pre[tmpr][k+del.dv].push_back(tmpt);
						dp[i+1][tmpr][k+del.dv]=dp[i][j][k]+del.ds;
					}
				}
			}
		}
	}
	
	
	
	return -1;
}

void path(){
	int j=ansr.dr;
	int k=ansr.dv;
	for (int i=ansr.ds-1;i>0;i--){
		ansp[i]=pre[j][k][i].power;
		j=pre[j][k][i].dr;
		k=pre[j][k][i].dv;
	}
}
int main()
{
	string terrain_src;
	
	
	cout<<"Input source of terrain data"<<endl;
	cnt=0;
	//cout<<sizeof(dp)<<' '<<sizeof(pre);
	terrain_src="./men-elite_data.txt";
	//cin>>terrain_src;
	//cout<<terrain_src<<endl;
	freopen(terrain_src.data(),"r",stdin);
	while (cin>>h[cnt++]);
	freopen("CON","r",stdin);
	cout<<"Input cyclers M E CP LT\n";
	//cin>>M>>E>>CP;
	scanf("%d %d %d",&M,&E,&CP,&LT);
	ms(dp,-1);
	for (int i=0;i<=100;i++){
		dp[0][i][0]=0;
	}
	cout<<solve();
	path();
	for (int i=1;i<ansr.ds;i++){
		cout<<ansp[i]<<' ';
	}
	//freopen(".out","w",stdout);
	
	
	return 0;
}
// 100 100 30
/*

const double c_r = 0.003;
const int m = 80;
const double g = 9.8;
const double eta = 0.95;
const double rho = 1.2;
const double c_wA = 0.31;
const int R = 1000;

double h[10000]; // 1km
int h_cnt;
double v_w[10000];

double M, E, CP;

tuple<int, int, int> delta(int s, int p, int v) // r,s,v
{
    double theta = atan2((h[s + 1] - h[s]), 0.01);
    double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
    double a = (-f * v / 10 + p) / (v / 10 * m);
    return make_tuple(CP - double(p) / E, (2 * v + int(10 * a)) / 2, (int)(10 * a));
}

int dp[18000][1145][350]; //[??][??][??]=??
tuple<int, int> pre[18000][1145][350];

int main()
{
    ios::sync_with_stdio(false);
    // ??????,10m per
    string terr_data_src;
    cout << "????????:";
    cin >> terr_data_src;
    freopen(terr_data_src.data(), "r", stdin);
    while (cin >> h[h_cnt++])
        ;
    // ???????
    cout << "???????(M E CP):";
    cin >> M >> E >> CP;

    bool flag = true;
    for (int i = 0;flag; i++)
    {
        for (int j = 0; j < 1145;j++)
            for (int k = 0; k < 350;k++)
            {
                int r, s, v;
                r, s, v = delta();
                dp[i + 1][j + r][k + v] = max(dp[i + 1][j + r][k + v], dp[i][j][k] + s);
            }
    }

    system("pause");
    return 0;
}


*/
