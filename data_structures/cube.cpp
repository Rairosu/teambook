/*
 * Cube class
 * state[3] - down side
 * state[1] - up side
 * state[4] - left side
 * state[5] - right side
 * state[2] - frost side
 * state[0] - back side
 *
 *
 */


int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int updown[4] = {0, 1, 2, 3};
int leftright[4] = {1, 4, 3, 5};
int now[4];

struct Cube {
    int state[6];

    Cube() {
        for (int i = 0; i < 6; ++i) {
            state[i] = i;
        }
    }

    void rotate(int dir) {
        if (dir == 1) {
            for (int i = 0; i < 4; ++i) {
                now[i] = state[updown[i]];
            }
            reverse(now, now + 3);
            reverse(now, now + 4);
            for (int i = 0; i < 4; ++i) {
                state[updown[i]] = now[i];
            }
        }
        if (dir == 2) {
            for (int i = 0; i < 4; ++i) {
                now[i] = state[updown[i]];
            }
            reverse(now + 1, now + 4);
            reverse(now, now + 4);
            for (int i = 0; i < 4; ++i) {
                state[updown[i]] = now[i];
            }
        }
        if (dir == 3) {
            for (int i = 0; i < 4; ++i) {
                now[i] = state[leftright[i]];
            }
            reverse(now + 1, now + 4);
            reverse(now, now + 4);
            for (int i = 0; i < 4; ++i) {
                state[leftright[i]] = now[i];
            }
        }
        if (dir == 0) {
            for (int i = 0; i < 4; ++i) {
                now[i] = state[leftright[i]];
            }
            reverse(now, now + 3);
            reverse(now, now + 4);
            for (int i = 0; i < 4; ++i) {
                state[leftright[i]] = now[i];
            }
        }
    }
    
    vector<int> get_state() const {
        vector<int> s;
        for (int i = 0; i < 6; ++i) {
            s.push_back(state[i]);
        }
        return s;
    }

    bool operator<(const Cube& other) const {
        return get_state() < other.get_state();
    }
};

