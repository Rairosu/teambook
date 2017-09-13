/*
 * This file contains Mo's algorithm signature.
 * This is sqrt decomposition of queries.
 *
 * Complexity: sorting O(nlogn), suppose add/remove comlexity is O(g), then
 *             overall comlexity is O(Q \sqrt{Q} g)
 *
 * Requirements: "algorithm"
 */


sort(q, q + Q, cmp);

int l = 0;
int r = 0;
for(int i = 0; i < Q; i++){
    int L = q[i].l;
    int R = q[i].r;
    while(curl < L){
        // remove 'l'
        ++l;
    }
    while(curl > L){
        // add 'l - 1'
        --l;
    }
    while(curr <= R){
        // add 'r'
        r++;
    }
    while(curr > R + 1){
        // remove 'r - 1'
        curr--;
    }
}

