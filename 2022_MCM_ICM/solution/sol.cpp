#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct status
{
	int dr, ds;
	int dv, power;
};

const double c_r = 0.003, g = 9.8, eta = 0.95, rho = 1.2, c_wA = 0.31;
const int m = 80, R = 1000;
double rx[10001], ry[10001];
double h[10001], v_w[10000];
double wind_theta, wind_vel;
double M, E, CP, LT;
int cnt, total_time;
int dp[1461][1001][301], ansp[1460], anss[1460];

status result;
vector<status> pre[1001][301];
void wind()
{
	freopen("ICM_MCM/men-elite-map_data.txt", "r", stdin);
	for (int i = 0; i < cnt; i++)
	{
		cin >> rx[i] >> ry[i];
	}
	freopen("CON", "r", stdin);
	// cin >> wind_theta >> wind_vel;
	int xiangxian;
	cout << "Input 0~7 vec";
	cin >> xiangxian;
	wind_theta = 3.1415 * xiangxian / 4;
	wind_vel = 0.1;
	for (int i = 0; i < cnt - 1; i++)
	{
		v_w[i] = wind_vel * cos(atan2((ry[i + 1] - ry[i]), (rx[i + 1] - rx[i])) - wind_theta);
	}
	cout << "wind prepared";
}
status delta(int s, int p, int v)
{
	status res;
	if (v / 10 * m == 0)
		return {0, 0, 0, 0};
	double theta = atan((h[s + 1] - h[s]) * 100);
	double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
	double a = (-f * v / 10 + p) / (v / 10 * m);
	res.dv = int(10 * a);
	// res.ds = v / 10;
	res.ds = (v + max(0, v + res.dv)) / 20;
	res.dr = 10 * (CP - double(p) / E);
	return res;
}
// 161.65 1.45 0.038 0.24
int solve()
{
	status del;

	int testmax = 0;

	int pmax = M;
	for (int p = 0; p <= pmax; p += 10)
	{
		del = delta(0, p, 10);
		if (del.ds < 0)
			continue;
		int tmpr = max(0, min(1000, 1000 + del.dr));
		int tmpv = max(0, min(300, del.dv));
		int tmps = del.ds;

		if (dp[1][tmpr][tmpv] <= tmps)
		{
			dp[1][tmpr][tmpv] = tmps;
			while (pre[tmpr][tmpv].size() <= 1)
				pre[tmpr][tmpv].push_back({-1, -1, -1, -1});
			pre[tmpr][tmpv][1] = {1000, 0, 1, p};
		}
	}

	for (int i = 1; i < 1460; i++)
	{
		bool testflag = false;

		if (i % 10 == 0)
			cout << i << endl;
		for (int j = 1000; j >= 0; j--)
			for (int k = 0; k <= 300; k++)
			{
				if (pre[j][k].size() <= i || pre[j][k][i].ds == -1)
					continue;
				if (dp[i][j][k] >= cnt)
				{
					result.ds = dp[i][j][k];
					result.dr = j;
					result.dv = k;
					return i;
				}
				int pmax = M * j / 1000 - LT * i;
				int prep = pre[j][k][i].power;
				if (prep - 100 > pmax)
				{
					prep = 1;
				}
				else
				{
					prep = max(1, prep - 100);
				}
				for (int p = prep; p <= min(prep + 200, pmax); p += 10)
				{
					testflag = true;
					del = delta(dp[i][j][k], p, k);
					if (del.ds < 0)
						continue;
					int tmpr = max(0, min(1000, j + del.dr));
					int tmpv = max(0, min(300, k + del.dv));
					int tmps = dp[i][j][k] + del.ds;

					if (dp[i + 1][tmpr][tmpv] <= tmps)
					{
						dp[i + 1][tmpr][tmpv] = tmps;
						testmax = max(testmax, tmps);
						while (pre[tmpr][tmpv].size() <= i + 1)
							pre[tmpr][tmpv].push_back({-1, -1, -1, -1});
						pre[tmpr][tmpv][i + 1] = {j, dp[i][j][k], k, p};
					}
				}
			}
		if (!testflag)
		{
			system("pause");
		}
	}

	return -1;
}
//
void path()
{
	int j = result.dr;
	int k = result.dv;
	for (int i = total_time; i > 0; i--)
	{
		ansp[i - 1] = pre[j][k][i].power;
		anss[i - 1] = pre[j][k][i].ds;
		int tj = pre[j][k][i].dr, tk = pre[j][k][i].dv;
		j = tj;
		k = tk;
	}
}
// 1th 481.73 6.31 18.56 0.03
// 2th 909.50 5.58 53.89 0.12
// 3th 637.3 35.3 4.7 0.20
// 4th 467.27 9.39 11.51 0.07
double peo[5][5] = {{481.73, 6.31, 18.56, 0.03}, {909.50, 5.58, 53.89, 0.12}, {637.3, 35.3, 4.7, 0.20}, {467.27, 9.39, 11.51, 0.07}};
int main()
{
	string terrain_src_path;
	cout << "choose people 0~3:\n";
	int pe;
	cin >> pe;
	cout << "Input source of terrain data: " << endl;
	// terrain_src_path = "ICM_MCM/men-elite_data.txt";
	terrain_src_path = "ICM_MCM/square_data.txt";
	{
		ifstream terrain(terrain_src_path.data());
		double tmpter;
		int counter = 0;
		while (terrain>>tmpter){
			counter++;
			if(counter>=4){
				h[cnt++] = tmpter * 0.1;
				counter = 0;
			}
		}
		h[cnt] = h[cnt - 1];
	}
	cout << "Input cyclers' M E CP LT: " << endl;
	M = peo[pe][0];
	E = peo[pe][1];
	CP = peo[pe][2];
	LT = peo[pe][3];
	// wind();
	//  cin >> M >> E >> CP >> LT;
	//  cout << delta(0, 160, 1).ds<<" "<<delta(0,160,1).dv;
	total_time = solve();
	cout << "Found: " << total_time << endl;
	path();
	for (int i = 0; i < total_time - 1; i++)
		cout << ansp[i] << ' ';
	cout << endl;
	for (int i = 0; i < total_time - 1; i++)
		cout << anss[i] << ' ';

	return 0;
}
