#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct status
{
	int dr, ds, dv;
	int power;
};

const double c_r = 0.003, g = 9.8, eta = 0.95, rho = 1.2, c_wA = 0.31;
const int m = 80, R = 1000;

double h[10001];
int cnt;
double v_w[10000];

const int INF = 0x3f3f3f3f;
status ansr;
short ansp[1460];
int total_time;

double M, E, CP, LT;
static int dp[1461][1001][301];
vector<status> pre[1001][301];
/*
tuple<int, int, int> delta(int s, int p, int v) // r,s,v
{
		double theta = atan2((h[s + 1] - h[s]), 0.01);
		double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
		double a = (-f * v / 10 + p) / (v / 10 * m);
		return make_tuple(CP - double(p) / E, (2 * v + int(10 * a)) / 2, (int)(10 * a));
}*/

status delta(int s, int p, int v)
{
	status res;
	double theta = atan((h[s + 1] - h[s]) * 100);
	double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
	double a = v / 10 * m != 0 ? (-f * v / 10 + p) / (v / 10 * m) : 0.1;
	res.dv = int(10 * a);
	res.ds = v / 10;
	res.dr = 10 * (CP - double(p) / E);
	return res;
}
// 161.65 1.45 0.038 0.24
int solve()
{
	status tmpt, del;
	for (int i = 0; i < 1460; i++)
	{
		// bool debugflag = false;
		cout << i << endl;
		for (int j = 1000; j >= 0; j--)
		{
			// bool flag = false;
			for (int k = 0; k <= 300; k++)
			{
				if (dp[i][j][k] >= INF)
					continue;
				// else
				//	debugflag = true;
				if (dp[i][j][k] >= cnt && dp[i][j][k] < INF)
				{
					ansr.ds = dp[i][j][k];
					ansr.dr = j;
					ansr.dv = k;
					return i;
				}
				int pmax = M * j / 1000 - LT * i;
				for (int p = 0; p <= pmax; p++)
				{
					del = delta(dp[i][j][k], p, k);
					if (del.ds < 0)
						continue;
					int tmpr = max(0, min(1000, j + del.dr));
					int tmpv = max(0, min(300, k + del.dv));
					int tmps = max(0, dp[i][j][k] + del.ds);
					if (dp[i + 1][tmpr][tmpv] < tmps || dp[i + 1][tmpr][tmpv] == INF)
					{
						dp[i + 1][tmpr][tmpv] = tmps;
						tmpt.ds = i; // this ds = time
						tmpt.dr = j;
						tmpt.dv = k;
						tmpt.power = p;
						if (i == 0)
							continue;
						while (pre[tmpr][tmpv].size() <= i + 1)
							pre[tmpr][tmpv].push_back({-1, -1, -1, -1});
						pre[tmpr][tmpv][i] = tmpt;
					}
				}
			}
		}
		// if (!debugflag)
		//	system("pause");
	}

	return -1;
}

void path()
{
	int j = ansr.dr;
	int k = ansr.dv;
	for (int i = total_time; i > 0; i--)
	{
		ansp[i] = pre[j][k][i].power;
		j = pre[j][k][i].dr;
		k = pre[j][k][i].dv;
	}
}

int main()
{
	cout << "Input cyclers' M E CP LT: ";
	M = 161.65;
	E = 1.45;
	CP = 0.38;
	LT = 0.24;
	// cin >> M >> E >> CP >> LT;
	string terrain_src;
	cout << "Input source of terrain data" << endl;
	terrain_src = "ICM_MCM/men-elite_data.txt";
	freopen(terrain_src.data(), "r", stdin);
	while (cin >> h[cnt++])
		;
	h[cnt] = h[cnt - 1];
	memset(dp, INF, sizeof(dp));
	for (int i = 0; i <= 1000; i++)
		dp[0][i][0] = 0;
	total_time=solve();
	cout << total_time;
	path();
	for (int i = 1; i < total_time; i++)
	{
		cout << ansp[i] << ' ';
	}
	// freopen(".out","w",stdout);
	return 0;
}
