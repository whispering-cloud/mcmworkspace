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
	int dr, ds, dv;
	int power;
};

const double c_r = 0.003, g = 9.8, eta = 0.95, rho = 1.2, c_wA = 0.31;
const int m = 80, R = 1000;

double h[10001], v_w[10000];
double M, E, CP, LT;
int cnt, total_time;
int dp[1461][1001][301], ansp[1460];

status result;
vector<status> pre[1001][301];

status delta(int s, int p, int v)
{
	status res;
	if (v / 10 * m == 0)
		return {0, 0, 0, 0};
	double theta = atan((h[s + 1] - h[s]) * 100);
	double f = c_r * m * g + rho * c_wA * (v / 10 - v_w[s]) * (v / 10 - v_w[s]) + g * sin(theta) * m;
	double a = (-f * v / 10 + p) / (v / 10 * m);
	res.dv = int(10 * a);
	res.ds = v / 10;
	res.dr = 10 * (CP - double(p) / E);
	return res;
}
// 161.65 1.45 0.038 0.24
int solve()
{
	status del;

	int pmax = M;
	for (int p = 0; p <= pmax; p++)
	{
		del = delta(0, p, 1);
		if (del.ds < 0)
			continue;
		int tmpr = max(0, min(1000, 1000 + del.dr));
		int tmpv = max(0, min(300, del.dv));
		int tmps = del.ds;

		if (dp[1][tmpr][tmpv] < tmps)
		{
			dp[1][tmpr][tmpv] = tmps;
			while (pre[tmpr][tmpv].size() <= 1)
				pre[tmpr][tmpv].push_back({-1, -1, -1, -1});
			pre[tmpr][tmpv][1] = {1000, 0, 1, p};
		}
	}

	for (int i = 1; i < 1460; i++)
	{
		if (i % 10 == 0)
			cout << i << endl;
		for (int j = 1000; j >= 0; j--)
			for (int k = 0; k <= 300; k++)
			{
				if (pre[j][k].size() <= i || pre[j][k][i].ds==-1)
					continue;
				if (dp[i][j][k] >= cnt/10)
				{
					result.ds = dp[i][j][k];
					result.dr = j;
					result.dv = k;
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
					int tmps = dp[i][j][k] + del.ds;

					if (dp[i + 1][tmpr][tmpv] < tmps)
					{
						dp[i + 1][tmpr][tmpv] = tmps;
						while (pre[tmpr][tmpv].size() <= i + 1)
							pre[tmpr][tmpv].push_back({-1, -1, -1, -1});
						pre[tmpr][tmpv][i + 1] = {j, i, k, p};
					}
				}
			}
	}

	return -1;
}

void path()
{
	int j = result.dr;
	int k = result.dv;
	for (int i = total_time; i > 0; i--)
	{
		ansp[i - 1] = pre[j][k][i].power;
		int tj = pre[j][k][i].dr, tk = pre[j][k][i].dv;
		j = tj;
		k = tk;
	}
}

int main()
{
	string terrain_src_path;
	cout << "Input source of terrain data: " << endl;
	terrain_src_path = "ICM_MCM/men-elite_data.txt";
	{
		ifstream terrain(terrain_src_path.data());
		while (terrain >> h[cnt++])
			h[cnt-1]*=0.1;
		h[cnt] = h[cnt - 1];
	}
	cout << "Input cyclers' M E CP LT: " << endl;
	M = 161.65;
	E = 1.45;
	CP = 0.38;
	LT = 0.24;
	// cin >> M >> E >> CP >> LT;
	total_time = solve();
	cout << "Found: " << total_time << endl;
	path();
	for (int i = 0; i < total_time - 1; i++)
		cout << ansp[i] << ' ';
	return 0;
}
