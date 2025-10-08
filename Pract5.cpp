#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << setw(4) << val;
        cout << '\n';
    }
}

void printMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char val : row)
            cout << setw(4) << val;
        cout << '\n';
    }
}

pair<int, string> lcs(const string& X, const string& Y, vector<vector<int>>& cost, vector<vector<char>>& dir) {
    int m = X.size(), n = Y.size();
    cost.assign(m + 1, vector<int>(n + 1, 0));
    dir.assign(m + 1, vector<char>(n + 1, ' '));

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (X[i - 1] == Y[j - 1]) {
                cost[i][j] = cost[i - 1][j - 1] + 1;
                dir[i][j] = 'D';
            } else if (cost[i - 1][j] >= cost[i][j - 1]) {
                cost[i][j] = cost[i - 1][j];
                dir[i][j] = 'U';
            } else {
                cost[i][j] = cost[i][j - 1];
                dir[i][j] = 'L';
            }

    string result;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (dir[i][j] == 'D') {
            result = X[i - 1] + result;
            --i; --j;
        } else if (dir[i][j] == 'U') {
            --i;
        } else {
            --j;
        }
    }
    return {cost[m][n], result};
}

pair<int, string> lrs(const string& S, vector<vector<int>>& cost, vector<vector<char>>& dir) {
    int n = S.size();
    cost.assign(n + 1, vector<int>(n + 1, 0));
    dir.assign(n + 1, vector<char>(n + 1, ' '));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (S[i - 1] == S[j - 1] && i != j) {
                cost[i][j] = cost[i - 1][j - 1] + 1;
                dir[i][j] = 'D';
            } else if (cost[i - 1][j] >= cost[i][j - 1]) {
                cost[i][j] = cost[i - 1][j];
                dir[i][j] = 'U';
            } else {
                cost[i][j] = cost[i][j - 1];
                dir[i][j] = 'L';
            }

    string result;
    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (dir[i][j] == 'D') {
            result = S[i - 1] + result;
            --i; --j;
        } else if (dir[i][j] == 'U') {
            --i;
        } else {
            --j;
        }
    }
    return {cost[n][n], result};
}

int main() {
    string X = "AGCCCTAAGGGCTACCTAGCTT";
    string Y = "GACAGCCTACAAGCGTTAGCTTG";
    vector<vector<int>> cost;
    vector<vector<char>> dir;

    cout << "TASK 1: LCS\n";
    auto [lcsLen, lcsStr] = lcs(X, Y, cost, dir);
    cout << "\nCost Matrix:\n"; printMatrix(cost);
    cout << "\nDirection Matrix:\n"; printMatrix(dir);
    cout << "\nLength: " << lcsLen << "\nLCS: " << lcsStr << "\n";

    string S = "AABCBDC";
    cout << "\nTASK 2: LRS\n";
    auto [lrsLen, lrsStr] = lrs(S, cost, dir);
    cout << "\nCost Matrix:\n"; printMatrix(cost);
    cout << "\nDirection Matrix:\n"; printMatrix(dir);
    cout << "\nLength: " << lrsLen << "\nLRS: " << lrsStr << "\n";

    return 0;
}
