//============================================================================
// Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition 
// is a palindrome.
//
// Return all possible palindrome partitioning of s.
//
// For example, given s = "aab",
// Return
//
//   [
//       ["aa","b"],
//       ["a","a","b"]
//   ]
//
// Complexity:
// Recursion + Memoization, O(n^2) time,  O(n^3) space
// DP, O(n^2) time, O(n^3) space
//============================================================================

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<string> > partition(string & s) {
        int N = s.size();
        vector<vector<bool> > dp1(N, vector<bool>(N, false));
        vector<vector<vector<string> > > dp2(N, vector<vector<string> >());
        for (int j = 0; j < N; j++) {
            for (int i = j; i >= 0; i--) {
                int l = j - i + 1;
                if (s[i] == s[j] && (l <= 2 || dp1[i + 1][j - 1])) {
                    dp1[i][j] = true;
                    if (i == 0) {
                        dp2[j].push_back(vector<string>(1, s.substr(0, l)));
                    }
                    else {
                        for (auto p : dp2[i - 1]) {
                            p.push_back(s.substr(i, l));
                            dp2[j].push_back(p);
                        }
                    }
                }
            }
        }
        return dp2[N - 1];
    }
};

int main() {
    Solution sol;
    string p0;

    {
        p0 = "aab";
        auto p1 = sol.partition(p0);
        for (auto it1 : p1) {
            for (auto it2 : it1) {
                cout << it2 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}