#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 10005;
double dp[MAXN];
short choice[1230][MAXN];
int primes[1230];
int prime_count = 0;
bool is_prime[MAXN];

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    // 1. Read all queries first to find the maximum N we actually need
    vector<int> queries(t);
    int max_n = 0;
    for(int i = 0; i < t; i++) {
        cin >> queries[i];
        if(queries[i] > max_n) max_n = queries[i];
    }
    
    // 2. Sieve only up to max_n
    for(int i = 0; i <= max_n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= max_n; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
            for (int j = i * i; j <= max_n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    // Global arrays are already 0, but resetting just in case
    for (int i = 0; i <= max_n; i++) dp[i] = 0.0;
    
    // 3. Ultra-Optimized Knapsack DP
    for (int i = 0; i < prime_count; i++) {
        int p = primes[i];
        
        int w[15];
        double l[15];
        int pcnt = 0;
        long long curr = p;
        while (curr <= max_n) {
            w[pcnt] = curr;
            l[pcnt] = log((double)curr);
            pcnt++;
            curr *= p;
        }
        
        int min_w = w[0];
        
        // Massive constant-factor optimization: Stop the loop when j drops below the smallest weight
        for (int j = max_n; j >= min_w; j--) {
            double best_val = dp[j];
            int best_choice = 0;
            
            for (int k = 0; k < pcnt; k++) {
                if (j >= w[k]) {
                    double val = dp[j - w[k]] + l[k];
                    if (val > best_val) {
                        best_val = val;
                        best_choice = w[k];
                    }
                } else {
                    break; // Weights strictly increase, so we can stop checking
                }
            }
            
            if (best_choice > 0) {
                dp[j] = best_val;
                choice[i][j] = best_choice;
            }
        }
    }
    
    // 4. Output processing
    for (int q = 0; q < t; q++) {
        int n = queries[q];
        vector<int> temp;
        int current_k = n; 
        
        for (int i = prime_count - 1; i >= 0; i--) {
            if (current_k >= 0 && choice[i][current_k] > 0) {
                temp.push_back(choice[i][current_k]);
                current_k -= choice[i][current_k];
            }
        }
        
        sort(temp.begin(), temp.end());
        
        int base = 1;
        int leftovers = current_k; 
        
        for (int j = 0; j < leftovers; j++) {
            cout << base << " ";
            base++;
        }
        
        for (size_t i = 0; i < temp.size(); i++) {
            int saved = base;
            for (int j = 0; j < temp[i]; j++) {
                if (j > 0) cout << base + j << " ";
            }
            cout << saved << " ";
            base += temp[i];
        }
        cout << "\n";
    }
    
    return 0;
}