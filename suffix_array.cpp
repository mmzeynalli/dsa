#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

vector <pair <int, double> > v;
vector <double> divided;

void divideTreasure(int st, int fin, double tres)
{
    if(st == fin)
    {
        divided[v[st].s] = tres;
        return;
    }
    if(v[st].f >= tres)
    {
        for(int i = st; i <= fin; i++)
            divided[v[i].s] = tres / (fin - st + 1);

        return;
    }

    double sum_left = 0, sum_right = 0, tres_left, tres_right;
    int i = st;

    while(i <= fin && sum_left + v[i].f <= tres)
    {
        sum_left += v[i].f;
        i++;
    }

    int mid = i - 1;

    while(i <= fin)
    {
        sum_right += v[i].f;
        i++;
    }


    if(sum_left == tres && sum_right == 0)
    {
        for(int j = st; j <= fin; j++)
            divided[v[j].s] = v[j].f;

        return;
    }
    else if (sum_left < tres && sum_right > tres)
    {
        tres_left = sum_left / 2;
        tres_right = tres - tres_left;
    }
    else if (tres >= sum_right)
    {
        tres_left = (sum_left / 2) + (tres - sum_right) / 2;
        tres_right = (sum_right / 2) + (tres - sum_left) / 2;
    }

    divideTreasure(st, mid, tres_left);
    divideTreasure(mid + 1, fin, tres_right);

}

int main()
{
    int n;
    double a, tres;

    cin >> n;

    divided.resize(n);

    for(int i = 0; i < n; i++)
    {
        cin >> a;
        v.push_back(make_pair(a, i));
    }

    cin >> tres;

    sort(v.begin(), v.end());

    divideTreasure(0, n - 1, tres);


    for(int i = 0; i < n; i++)
        cout << fixed << setprecision(9) << divided[i] << ' ';

}
