/*
 * Spotify Puzzles, Cats vs Dogs
 * https://gist.github.com/morazow/4966758
 *
 * Solution similar to Bilateral Projects
 * - find max independent set size, V
 * - V = N - max matching size
 * - in bipartite graph
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 500

int N;
vector<int> adj[MAXN+1];
int match[MAXN+1];
int visited[MAXN+1];

int dfs(int u) {

  if (visited[u]) 
    return 0;

  visited[u] = 1;
  for (int i = 0; i < adj[u].size(); i++) 
    if ( match[ adj[u][i] ] == -1 || dfs(match[ adj[u][i] ]) ) {
      match[ adj[u][i] ] = u;
      return 1;
    }

  return 0;
}

int main() {
  int c, d, T;
  string s1, s2;
  vector<pair<string, string> > cats, dogs;

  for (cin >> T; T--; ) {

    cin >> c >> d >> N;
    cats.clear();
    dogs.clear();

    for (int i = 0; i < N; i++) {
      cin >> s1 >> s2;
      if (s1[0] == 'C') 
        cats.push_back(make_pair(s1, s2));
      else
        dogs.push_back(make_pair(s1, s2));
    }

    for (int i = 0; i < cats.size(); i++) {
      adj[i].clear();
      for (int j = 0; j < dogs.size(); j++) 
        if (dogs[j].first == cats[i].second || cats[i].first == dogs[j].second)
          adj[i].push_back(j);
    }

    memset(&match, 0xffff, sizeof(match));
    for (int i = 0; i < cats.size(); i++) {
      memset(&visited, 0, sizeof(visited));
      dfs(i);
    }

    int ans = 0;
    for (int i = 0; i < dogs.size(); ans += (match[i++] != -1));
    cout << N - ans << endl;
  }

  return 0;
}
