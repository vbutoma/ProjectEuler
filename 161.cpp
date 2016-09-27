#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

const long N = 12;
const long M = 9;

struct trimino{
    pair<long, long> first;
    pair<long, long> second;
    pair<long, long> third;
};

vector<trimino> pieces;

long row_num[N * M];
long column_num[N * M];

map<string, ll> F;

void init_triminos(){
    // 11 11 1   1 1 111
    // 1   1 11 11 1
    //             1
    trimino piece;
    piece.first = mp(0, 0);
    piece.second = mp(1, 0);
    piece.third = mp(0, 1);
    pieces.pb(piece);

    piece.first = mp(0, 0);
    piece.second = mp(1, 0);
    piece.third = mp(1, 1);
    pieces.pb(piece);

    piece.first = mp(0, 0);
    piece.second = mp(0, 1);
    piece.third = mp(1, 1);
    pieces.pb(piece);

    piece.first = mp(0, 0);
    piece.second = mp(0, 1);
    piece.third = mp(-1, 1);
    pieces.pb(piece);

    piece.first = mp(0, 0);
    piece.second = mp(0, 1);
    piece.third = mp(0, 2);
    pieces.pb(piece);

    piece.first = mp(0, 0);
    piece.second = mp(1, 0);
    piece.third = mp(2, 0);
    pieces.pb(piece);
}


ll cover(long n, long* grid){
    long row = n / M;
    long column = n % M;
    ll ans = 0;

    if (row == N && !column)
        return 1; //filled !

    //count Hash of state (n, grid)
    string h = "";
    stringstream s_stream;
    s_stream << n;
    h = s_stream.str() + " ";
    s_stream.str("");
    for (int i = n; i < min(n + 2 * M, N * M); i++)
        s_stream << grid[i];

    h = h + s_stream.str();

    if (F.count(h) > 0)
        return F[h];

    assert(n < N*M);
    if (grid[n]){
        F[h] = cover(n + 1, grid);
        return F[h];
    }

    long index = 0;
    for (auto piece : pieces){
        vector<pair<long, long> > cur_trimino;
        cur_trimino.pb(piece.first);
        cur_trimino.pb(piece.second);
        cur_trimino.pb(piece.third);
        long is_bad = false;
        for (auto p : cur_trimino){
            long x = p.first;
            long y = p.second;
            if (x + column < 0 || column + x >= M || row + y >= N ||
                grid[(row + y) * M + (column + x)] > 0) is_bad = true;;
        }
        if (is_bad)
            continue;
        long *g = new long[N * M];
        for (int i = 0; i < N * M; i++)
            g[i] = grid[i];
        for (auto p : cur_trimino){
            long x = p.first;
            long y = p.second;
            g[(row + y) * M + (column + x)] = 1;
        }
        ans += cover(n + 1, g);
        index++;
    }
    F[h] = ans;
    return ans;
}

int main()
{
    init_triminos();

    long *grid = new long[N * M];
    for (int i = 0; i < N * M; i++)
        grid[i] = 0;

    cout << cover(0, grid);
    return 0;
}

