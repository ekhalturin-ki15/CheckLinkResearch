#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<char, char> lower;

void pars(ifstream& in, map<int, string>& m, int start)
{
    int    id = start + 1;
    string s;
    string cash;
    while (in >> s)
    {
        for (auto& it : s)
        {
            if (lower.count(it))
                it = lower[it];
        }

        string ok = s;

        int i = 0;
        for (i = 0; i < 2; ++i)
        {
            try
            {
                if (!isdigit(s.at(0)))
                    s = s.substr(1);

                int num = stoi(s);
                if (num == (id))
                {
                    if (id > start)
                        m[id - 1] = cash;
                    ++id;
                    cash = "";
                }
                break;
            }
            catch (...)
            {
            }
            if (s.size())
                s.pop_back();
        }
        if (i == 2)
        {
            if (cash.size())
                cash += " ";
            cash += ok;
        }
    }
    m[id - 1] = cash;
}
struct ST
{
    string sov;
    int    k1;
    int    k2;

    bool operator<(ST r)
    {
        if (sov.size() != r.sov.size())
            return sov.size() > r.sov.size();
        return k1 > r.k1;
    }
};

#define HOLD 3
int main()
{
    // FILE* IN, * OUT;
    // freopen_s(&IN, "input.txt", "r", stdin);
    // freopen_s(&OUT, "output.txt", "w", stdout);

    ifstream in1("input.txt");
    ifstream in2("who.txt");
    ofstream out1("output.txt");

    map<int, string> m;
    map<int, string> n;

    string s1, s2;
    in1 >> s1 >> s2;
    vector<char> v1(s1.size()), v2(s2.size());
    
    
    {
        int i = 0;
        for (const auto& it : s1)
            v1[i++] = it;
        i = 0;
        for (const auto& it : s2)
            v2[i++] = it;

        i = 0;
        for (const auto& it : s1)
        {
            lower[v2[i]] = v1[i];
            ++i;
        }
    }


    pars(in1, m, 2);
    pars(in2, n, 1);

    map<int, ST> res;

    for (auto& [k1, s1] : m)
    {
        for (auto& [k2, s2] : n)
        {
            string ans;
            int    ma = 0;
            for (int shift = 0; shift < int(s2.size()) - 1; ++shift)
            {
                string s;
                for (int i = shift; i < s2.size(); ++i)
                {
                    s.push_back(s2[i]);
                    if (s1.find(s) != string::npos)
                    {
                        if (ans.size() < s.size())
                            ans = s;
                    }
                }
            }
            if (ans.size() > HOLD)
            {
                if (res.count(k1))
                {
                    if (res[k1].sov.size() < ans.size())
                    {
                        res[k1] = { ans, k1, k2 };
                    }
                }
                else
                {
                    res[k1] = { ans, k1, k2 };
                }
            }
        }
    }

    vector<ST> v;
    for (auto& [k, it] : res)
    {
        v.push_back(it);
    }
    sort(v.begin(), v.end());
    for (auto& it : v)
    {
        out1 << it.k1 << " " << it.k2 << " " << it.sov << "\n";
    }
}
