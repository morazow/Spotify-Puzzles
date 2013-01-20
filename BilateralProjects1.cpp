#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<stack>
#include<set>

using namespace std;

#define MAXN 2001
#define MAXM 10001

int E;
int N, M;

vector<int> adj[MAXN];
int matched[MAXN];
int dist[MAXN];

set<int> L, R;

int Dfs(int u) {
  int v;
  for (int i = 0; i < adj[u].size(); i++) {
    v = adj[u][i];
    if (dist[v] != dist[u] + 1) continue;
    dist[v] = 0;
    if (matched[v] == -1 || Dfs(matched[v]))
    {
      matched[v] = u;
      matched[u] = v;
      return 1;
    }
  }
  return 0;
}

int Bfs() {
  int u, v, flag = 0;
  queue<int> Q;

  memset(&dist, 0, sizeof(dist));
  for (int i = 0; i < 1000; i++)
    if (matched[i] == -1) Q.push(i);

  while (!Q.empty()) {
    u = Q.front();
    Q.pop();

    for (int i = 0; i < adj[u].size(); i++) {
      v = adj[u][i];
      if (dist[v]) continue;
      dist[v] = dist[u] + 1;
      if (matched[v] != -1) {
        dist[matched[v]] = dist[v] + 1;
        Q.push(matched[v]);
      }
      else
        flag = 1;
    }
  }

  return flag;
}

void Matching() {
  int res = 0;

  memset(&matched, 0xffff, sizeof(matched));

  while (Bfs())
  {
    for (int i = 0; i < 1000; i++)
      if (matched[i] == -1 && Dfs(i)) ++res;
  }

  printf("%d\n", res);

  set<int> T;
  for (int u, i = 0; i < 1000; i++)
    if (matched[i] == -1) {
      T.insert(i);

      stack<int> S;
      S.push(i);
      while (!S.empty()) {
        u = S.top(); S.pop();
        for (int v, j = 0; j < adj[u].size(); j++) {
          v = adj[u][j];
          if (T.find(v) != T.end()) continue;
          if (u == matched[v]) continue;

          T.insert(v);
          if (matched[v] != -1) {
            T.insert(matched[v]);
            S.push(matched[v]);
          }
        }
      }
    }

  set<int> tmp1, tmp2, result;
  set_difference(L.begin(), L.end(), T.begin(), T.end(), inserter(tmp1, tmp1.end()));
  set_intersection(R.begin(), R.end(), T.begin(), T.end(), inserter(tmp2, tmp2.end()));
  set_union(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(result, result.end()));

  for (set<int>::iterator it = result.begin(); it != result.end(); it++) {
    printf("%d ", *it + 1000);
  }
  printf("\n");
}

int main() {
  int u, v;

  scanf("%d", &N);
  for (int i = 0; i < N; i++)
  {
    scanf("%d %d", &u, &v);
    u -= 1000;
    v -= 1000;
    adj[u].push_back(v);
    adj[v].push_back(u);
    L.insert(u);
    R.insert(v);
  }

  Matching();

  return 0;

}

