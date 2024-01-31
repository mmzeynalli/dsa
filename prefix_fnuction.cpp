#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdbool>

using namespace std;


#define pb push_back
#define mp make_pair

#define FAST_READ ios_base::sync_with_stdio(0), cin.tie(), cout.tie()

typedef long long ll;

vector<ll> pi;

void init_prefix(char* s)
{
	ll n = strlen(s);

	pi.resize(n);

	pi[0] = 0;

	for (int i = 1; i < n; i++)
	{
		int j = pi[i - 1];

		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];

		if (s[i] == s[j]) pi[i] = j + 1; 
		else pi[i] = 0; //if not found
	}
		
}

int main()
{
	int n, q;

	char* txt = (char*)calloc(0, sizeof(char));

	scanf("%s", txt);

	init_prefix(txt);

	scanf("%d", &n);

	while (n--)
	{
		scanf("%d", &q);
		printf("%d", pi[q]);
	}

	
}