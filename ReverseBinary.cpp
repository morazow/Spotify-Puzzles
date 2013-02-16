/*
 * Spotify Puzzles, Reversed Binary Numbers
 * https://gist.github.com/morazow/4966257
 *
 */
#include<iostream>
using namespace std;

int main() {
    unsigned long n, res = 0;
    cin >> n;
    while (n) {
        res <<= 1;
        res |= (n & 0x1);
        n >>= 1;
    }
    cout << res << endl;
    return 0;
}
