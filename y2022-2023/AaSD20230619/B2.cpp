#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll INF = LONG_LONG_MAX;

ll n, m;
vector<vector<ll>> graph;
vector<ll> deph, used, capac, flow;
vector<bool> visited;
vector<pair<ll, ll>> member;
queue<ll> q;


void print_vector(vector<ll> &a) {
    for (auto i: a) {
        cout << i << " ";
    }
    cout << endl;
}

void print_vector_vector(vector<vector<ll>> &a) {
    for (auto i: a) {
        for (auto j: i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool bfs(ll s, ll t) {
    deph.assign(n, INF);
//    print_vector(deph);
    deph[s] = 0;
    q.push(s);

    while (!q.empty()) {
        ll now = q.front();
        q.pop();
        for (ull j = 0; j < graph[now].size(); j++) {
            ll number = graph[now][j];
            ll to = member[number].second;
//            print_vector(deph);
//            print_vector_vector(flow);
//            cout << endl;
            ll capacity = capac[number] - flow[number];
            if (deph[to] == INF && capacity > 0) {
                deph[to] = deph[now] + 1;
                q.push(to);
            }
        }
    }
//    print_vector(deph);
//    cout << endl;
    return deph[t] != INF;
}

void simple_dfs(ll now) {
    visited[now] = true;
    for (ll number: graph[now]) {
        ll to = member[number].second;
        if (capac[number] - flow[number] > 0 && !visited[to]) {
            simple_dfs(to);
        }
    }
}

ll dfs(ll now, ll t, ll f) {
    if (now == t || f == 0) {
        return f;
    }

    while (used[now] < graph[now].size()) {

//        print_vector(deph);
//        print_vector_vector(flow);
//        cout << endl;
        ll number = graph[now][used[now]];
        ll to = member[number].second;
        if (deph[to] == deph[now] + 1) {
            ll add = dfs(to, t, min(f, capac[number] - flow[number]));
            if (add > 0) {
                flow[number] += add;
                if (number % 2 == 0) {
                    flow[number + 1] -= add;
                } else {
                    flow[number - 1] -= add;
                }
                return add;
            }
        }

        used[now]++;
    }

    return 0;
}

ll maxflow(ll s, ll t) {
    ll total_flow = 0;

    bool work = bfs(s, t);
    while (work) {
        used.assign(n, 0);
        ll add_flow = dfs(s, t, INF);
        while (add_flow > 0) {
            total_flow += add_flow;
            add_flow = dfs(s, t, INF);
        }
        work = bfs(s, t);
    }

    return total_flow;
}

void print_flow() {
    for (ll i = 0; i < 2 * m; i += 2) {
        cout << flow[i] << endl;
    }
}

void print_cut(ll s, ll max_flow) {
    simple_dfs(s);
    vector<ll> edges;
    for (ll i = 0; i < member.size(); i += 2) {
        ll from = member[i].first;
        ll to = member[i].second;
        if ((visited[from] && !visited[to]) || (visited[to] && !visited[from])) {
            edges.push_back(i / 2);
        }
    }
    cout << edges.size() << " " << max_flow << endl;
    for (ll i: edges) {
        cout << i + 1 << " ";
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    deph.resize(n);

    graph.resize(n);
    used.resize(n);
    visited.resize(n);
    visited.assign(n, false);
    ll a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        graph[a].push_back(2 * i);
        graph[b].push_back(2 * i + 1);
        member.push_back({a, b});
        member.push_back({b, a});
        capac.push_back(c);
        capac.push_back(c);
        flow.push_back(0);
        flow.push_back(0);
    }
//    print_vector_vector(graph);
//    print_vector_vector(rem_cap);
//    print_vector_vector(capac);
    ll max_flow = maxflow(0, n - 1);
//    print_vector_vector(flow);
//    cout << max_flow << endl;
//    print_flow();
    print_cut(0, max_flow);

    return 0;
}