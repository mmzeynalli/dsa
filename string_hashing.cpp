#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdbool>

#define FAST_READ ios_base::sync_with_stdio(0), cin.tie(), cout.tie()

#define pb push_back
#define mp make_pair

typedef long long ll;

const int m = 1e9 + 9;
const int p = 31;

using namespace std;


vector<ll> p_val;
vector<ll> h_m;

void init_p(string s)
{
	ll n = s.size();

	if (n > p_val.size())
	{
		int i = p_val.size();
		if (!i) i++;

		p_val.resize(n);

		p_val[0] = 1;

		for (; i < n; i++)
			p_val[i] = (p_val[i - 1] * p) % m;
	}
}

ll hash_value(string s)
{
	ll h = 0;

	for (int i = 0; i < s.size(); i++)
		if (s.at(i) == ' ')
			h = (h + (s.at(i)) * p_val[i]) % m;
		else
			h = (h + (s.at(i) - 'a' + 1) * p_val[i]) % m;

	return h;
}


int is_substr(string t, string s)
{
	ll S = s.size();
	ll T = t.size();

	ll h_s = hash_value(s);

	vector<ll> occurs;

	for (int i = 0; i + S <= T; i++)
	{
		ll curr_h = (h_m[i + S] + m - h_m[i]) % m;

		if (curr_h == (h_s * p_val[i]) % m)
			return 1;
	}

	return 0;

}


vector<ll> get_indices(string t, string s)
{
	ll S = s.size();
	ll T = t.size();

	ll h_s = hash_value(s);

	vector<ll> occurs;

	for (int i = 0; i + S <= T; i++)
	{
		ll curr_h = (h_m[i + S] + m - h_m[i]) % m;

		if (curr_h == (h_s * p_val[i]) % m)
			occurs.pb(i);
	}

	return occurs;
}

ll distinct_substr(string s, ll len)
{
	ll n = s.size();
	if (len == n) return 1;

	set<ll> occurs;

	for (int i = 0; i <= n - len; i++)
	{
		ll curr_h = (h_m[i + len] + m - h_m[i]) % m;
		curr_h = (curr_h * p_val[n - 1 - i]) % m;
		
		occurs.insert(curr_h);
	}

	return occurs.size();
}

ll get_instances(string t, ll len)
{
	ll T = t.size();

	/*FOR CONSTANT TEXT*/
	h_m.resize(0);
	h_m.resize(T + 1, 0);

	for (int i = 0; i < T; i++)
		if (t.at(i) == ' ')
			h_m[i + 1] = (h_m[i] + (t.at(i)) * p_val[i]) % m;
		else
			h_m[i + 1] = (h_m[i] + (t.at(i) - 'a' + 1) * p_val[i]) % m;

	
	ll cnt = 1;

	ll h_s = h_m[len];

	for (int i = len; i + len <= T; i += len)
	{
		ll curr_h = (h_m[i + len] + m - h_m[i]) % m;

		if (curr_h == (h_s * p_val[i]) % m)
			cnt++;
		
	}

	return cnt;
}


int main()
{
	FAST_READ;

	ll n;
	string s;

	cin >> n;

	cin.ignore(10, '\n');

	ll longest;

	for (int i = 1; i <= n; i++)
	{
		getline(cin, s);

		init_p(s);

		cout << "Case #" << i << ": " << s.size();

		for (int j = 2; j <= s.size(); j++)
		{
			longest = 0;

			for (int k = s.size(); k >= j; k--)
			{
				if (k % j) continue;

				for (int a = 0; a <= s.size() - k; a++)
				{
					if (get_instances(s.substr(a, k), k / j) == j)
					{
						longest = k;
						break;
					}
				}

				if (longest == k) break;
				
			}

			cout << " " << longest;
		}

		cout << endl;
		
	}
}