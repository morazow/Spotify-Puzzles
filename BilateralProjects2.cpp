#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<set>
#include<cassert>

using namespace std;

#define MAXN 2001
#define MAXM 10001

class BilateralProjects {
  int E;
  int N, M;

  vector<int> adj[MAXN];
  int match[MAXN];
  int dist[MAXN];

  set<int> L, R;

  bool Dfs(int);
  bool Bfs();

 public:
  BilateralProjects(int _E) : E(_E) {};
  ~BilateralProjects() { }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    L.insert(u);
    R.insert(v);
  }

  void Solve() {
    int k = getMatching();
    set<int> ids = getCover();

    assert(k == ids.size());

    printf("%d\n", k);
    for (set<int>::iterator it = ids.begin(); it != ids.end(); it++)
      printf("%d ", *it + 1000);
    printf("\n");
  }

  int getMatching();
  set<int> getCover();

};

int main() {
  int M, u, v;

  scanf("%d", &M);
  BilateralProjects *BL = new BilateralProjects(M);

  for (int i = 0; i < M; i++) {
    scanf("%d %d", &u, &v);
    u -= 1000;
    v -= 1000;
    BL->addEdge(u, v);
  }
  BL->Solve();

  delete BL;

  return 0;
}

set<int> BilateralProjects::getCover() {
  set<int> T;

  for (int u, i = 0; i < 1000; i++) {
    if (match[i] != -1)
      continue;

    T.insert(i);
    stack<int> S;
    S.push(i);
    while (!S.empty()) {
      u = S.top();
      S.pop();

      for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
        if (T.find(*it) != T.end())
          continue;
        if (match[*it] == u)
          continue;

        T.insert(*it);
        if (match[*it] != -1) {
          T.insert(match[*it]);
          S.push(match[*it]);
        }
      }
    }
  }

  set<int> tmp1, tmp2, result;

#define ALL(a) (a).begin(), (a).end()
  set_difference(ALL(L), ALL(T), inserter(tmp1, tmp1.begin()));
  set_intersection(ALL(R), ALL(T), inserter(tmp2, tmp2.begin()));
  set_union(ALL(tmp1), ALL(tmp2), inserter(result, result.begin()));

  return result;
}

int BilateralProjects::getMatching() {
  int res = 0;
  memset(&match, 0xffff, sizeof(match));

  while (Bfs()) {
    for (int i = 0; i < 1000; i++)
      if (match[i] == -1 && Dfs(i))
        ++res;
  }

  return res;
}

bool BilateralProjects::Dfs(int u) {

  for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
    if (dist[u] + 1 != dist[*it])
      continue;
    dist[*it] = 0;
    if (match[*it] == -1 || Dfs(match[*it])) {
      match[u] = *it;
      match[*it] = u;
      return true;
    }
  }

  return false;
}

bool BilateralProjects::Bfs() {
  bool flag = false;
  queue<int> Q;

  memset(&dist, 0, sizeof(dist));
  for (int i = 0; i < 1000; i++)
    if (match[i] == -1)
      Q.push(i);

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
      if (dist[*it])
        continue;

      dist[*it] = dist[u] + 1;
      if (match[*it] != -1) {
        dist[match[*it]] = dist[*it] + 1;
        Q.push(match[*it]);
      }
      else
        flag = true;
    }
  }

  return flag;
}
