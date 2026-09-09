#include <iostream>
#include <vector>
#include <climits>

void printParenthesis(int i, int j, const std::vector<std::vector<int>>& bracket, char& name) {
    if (i == j) {
        std::cout << name++;
        return;
    }
    std::cout << "(";
    printParenthesis(i, bracket[i][j], bracket, name);
    printParenthesis(bracket[i][j] + 1, j, bracket, name);
    std::cout << ")";
}

void matrixChainOrder(const std::vector<int>& p) {
    int n = p.size() - 1;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> bracket(n + 1, std::vector<int>(n + 1, 0));

    for (int L = 2; L <= n; ++L) {
        for (int i = 1; i <= n - L + 1; ++i) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + (p[i - 1] * p[k] * p[j]);
                
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    std::cout << "Minimum scalar multiplications: " << dp[1][n] << "\n";
    std::cout << "Optimal Parenthesization: ";
    char name = 'A';
    printParenthesis(1, n, bracket, name);
    std::cout << "\n";
}

int main() {
    std::vector<int> dimensions = {40, 20, 30, 10, 30};
    matrixChainOrder(dimensions);
    return 0;
}
