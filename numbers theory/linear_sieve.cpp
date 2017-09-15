/*
 *
 * Eratosthenes' sieve.
 *
 * Complexity: O(n).
 *
 * Usage:
 *   - lp[x] = true if x is prime
 *   - pr contains all primes <= N
 *
 */

const int N = (int)1e7;
int lp[N + 1];
vector<int> pr;
 
void sieve() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() &&
                pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}
