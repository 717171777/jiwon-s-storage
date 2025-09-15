#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;
struct P { ll x, y; };

ll d(P p1, P p2) { return abs(p1.x - p2.x) + abs(p1.y - p2.y); }

P find(const vector<P>& p, int n, int si, ll dist, bool cw) {
    P pos = p[si];
    int idx = si;
    while (dist > 0) {
        int ni = cw ? (idx + 1) % n : (idx - 1 + n) % n;
        ll sl = d(pos, p[ni]);
        if (!sl) {
            idx = ni;
            if (idx == si) break;
            continue;
        }
        if (dist >= sl) {
            dist -= sl;
            pos = p[ni];
            idx = ni;
        } else {
            ll dx = p[ni].x - pos.x;
            if (dist <= abs(dx)) {
                pos.x += (dx > 0 ? dist : -dist);
            } else {
                pos.x = p[ni].x;
                ll rd = dist - abs(dx);
                ll dy = p[ni].y - pos.y;
                pos.y += (dy > 0 ? rd : -rd);
            }
            dist = 0;
        }
    }
    return pos;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<P> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
    ll t;
    cin >> t;
    ll L = 0, db = 0;
    int c2s = n / 2 - 1;
    for (int i = 0; i < n; ++i) {
        ll sl = d(p[i], p[(i + 1) % n]);
        L += sl;
        if (i < c2s) db += sl;
    }
    if (!L) {
        cout << p[0].x << " " << p[0].y << "\n" << p[0].x << " " << p[0].y << "\n";
        return 0;
    }
    ll rd = t % L;
    P pA = find(p, n, 0, rd, 1);
    P pB = find(p, n, c2s, rd, 0);
    
    if (t < L) {
        if (2 * t >= db || 2 * t >= L - db) swap(pA, pB);
    } else {
        ll tt = 2 * t, c = (tt / L) * 2, r = tt % L;
        if (db * 2 == L) {
            if (r >= db) c++;
        } else {
            if (r >= db) c++;
            if (r >= L - db) c++;
        }
        if (c % 2) swap(pA, pB);
    }
    
    cout << pA.x << " " << pA.y << "\n";
    cout << pB.x << " " << pB.y << "\n";
    
    return 0;
}