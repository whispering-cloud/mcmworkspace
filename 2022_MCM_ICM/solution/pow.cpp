#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(arr,val) memset(arr,val,sizeof(arr))
#define ll long long
#define iv inline void
using namespace std;

const double c_r = 0.003;
const int m = 80;
const double g = 9.8;
const double eta = 0.95;
const double rho = 1.2;
const double c_wA = 0.31;
const int R = 1000;

double h[10000];
double v_w[10000];

double M,E,CP;


struct status{
	int dr;
	double ds,dv;
};


status delta(int s,int p,int v){
	status res;
	double theta = atan2((h[s * 100 + 1] - h[s * 100]) , 0.01);
	double f = c_r * m * g + rho * c_wA * (v - v_w[s*100]) * (v - v_w[s*100]) + g * sin(theta) * m;
	double a = ( -f * v + p)/(v * m);
	res.dv = v + a;
	res.ds = (double(v + res.dv)) / 2 + s;
	res.dr = CP - double(p) / E;
	return res;
}

int main()
{
	//freopen(".out","w",stdout);
	//freopen(".in","r",stdin);
	
	
	
	
	return 0;
}

