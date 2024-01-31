#include <bits/stdc++.h>

using namespace std;

#define FAST_READ ios_base::sync_with_stdio(0), cin.tie(), cout.tie()
#define pb push_back
#define mp make_pair
#define INF 2100000000
#define MAX 2005
#define f first
#define s second

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

vector<ll> used;
vector<vector<ld> > v;
vector<ld> d;

ll n, m, k, a, b, w, win, st, p;
vector<ll> winners;

ll find_min()
{
	ld maxi = -1, v;

	for (int i = 1; i <= n; i++)
		if (!used[i] && d[i] > maxi) maxi = d[i], v = i;

	return v;
}

void relax(ll from, ll to)
{
	d[to] = max(d[to], d[from] * v[from][to]);
}

void dijkstra(ll st)
{
	d[st] = 1;

	ll from;

	for (int i = 1; i < n; i++)
	{
		from = find_min();

		for (int to = 1; to <= n; to++)
			if (!used[to]) relax(from, to);

		used[from] = 1;
	}
}

int main()
{
	cin >> n >> k;

	used.resize(n + 1, 0);
	d.resize(n + 1, 0);
	v.resize(n + 1, vector<ld>(n + 1, 0));

	while (k--)
	{
		cin >> a >> b >> p;
		v[a][b] = v[b][a] = p / 100.0;
	}

	dijkstra(1);

	cout << fixed << setprecision(6) << d[n] * 100.0 << " percent" << endl;

	return 0;
}