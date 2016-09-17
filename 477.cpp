#include <iostream>
#include <deque>
#include <vector>
#include <stack>

using namespace std;

#define ll long long

const ll base = (ll)1e9 + 7;
const long N = (long)1e8;

stack<long> s;

ll v = 0;
ll sum = 0;

int main()
{
    s.push(0);
    for (int i = 1; i < N; i++){
        v = (v * v + 45) % base;
        s.push(v);
        sum += v;

        while (s.size() > 2){
            ll c = s.top(); s.pop();
            ll b = s.top(); s.pop();
            ll a = s.top(); s.pop();

            if (b >= max(a, c)){
                s.push(a - b + c);
            }else{
                s.push(a), s.push(b), s.push(c);
                break;
            }
        }

    }

    deque<long> d;
    while (s.size()){
        d.push_back(s.top());
        s.pop();
    }
    ll score = 0;

    cout << d.size() << endl;
    for (auto item : d)
        cout << item << endl;

    long player = 0;
    while (d.size()){

        if (d.front() >= d.back()){
            score += player ? -d.front() : d.front();
            d.pop_front();
        }else{
            score += player ? -d.back() : d.back();
            d.pop_back();
        }
        player ^= 1;
    }
    //x - y = score
    //x + y = sum
    cout << (score + sum) / 2;
    return 0;
}