/*
 * Sporify Puzzles, Zipf's Song
 * https://gist.github.com/morazow/4966950 
 *
 * Solution 
 * - stable sorting
 *
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
struct song {
  unsigned long long value;
  int order;
  string name;
  
  song() {}
  song(unsigned long long v, int idx, string _name) :
      value(v), order(idx), name(_name) { }

};
vector<song> songs;

bool compare(const song a, const song b) {
  if (a.value == b.value)
    return a.order < b.order;
  return a.value > b.value;
}

int main() {
  unsigned long long v;
  char name[50];

  scanf("%d%d\n", &N, &M);
  songs.reserve(N);
  for (int i = 0; i < N; i++) {
    scanf("%llu %s\n", &v, name);
    songs.push_back(song(v * (i+1), i, string(name)));
  }

  sort(songs.begin(), songs.end(), compare);
  for (int i = 0; i < M; i++) 
    printf("%s\n", songs[i].name.c_str());

  return 0;
}
