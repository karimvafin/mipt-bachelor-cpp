#include "tasks.h"

int sum(const std::vector<int>& v) {
    int s = 0;
    for (int x : v) {
        s += x;
    }
    return s;
}

std::vector<int> filter_even(const std::vector<int>& v) {
    std::vector<int> res;
    for (int x : v) {
        if (x % 2 == 0) {
            res.push_back(x);
        }
    }
    return res;
}

void rotate_left(std::vector<int>& v, std::size_t k) {
    k %= v.size();
    std::vector<int> res;

    for (std::size_t i = k; i < v.size(); ++i) {
        res.push_back(v[i]);
    }
    for (std::size_t i = 0; i < k; ++i) {
        res.push_back(v[i]);
    }

    v = res;
}

std::vector<int> remove_duplicates(const std::vector<int>& v) {
    std::vector<int> res;
    for (int x : v) {
        bool ok = true;
        for (int y : res) {
            if (x == y) {
                ok = false;
                break;
            }
        }
        if (ok) {
            res.push_back(x);
        }
    }
    return res;
}

std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> res;
    for (const auto& row : matrix) {
        for (int x : row) {
            res.push_back(x);
        }
    }
    return res;
}

std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> res;
    std::size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            res.push_back(a[i]);
            ++i;
        } else {
            res.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size()) {
        res.push_back(a[i]);
        ++i;
    }
    while (j < b.size()) {
        res.push_back(b[j]);
        ++j;
    }
    return res;
}

int max_subarray_sum(const std::vector<int>& v) {
    int cur = v[0];
    int best = v[0];
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (cur < 0) {
            cur = v[i];
        } else {
            cur += v[i];
        }

        if (cur > best) {
            best = cur;
        }
    }
    return best;
}

std::vector<std::vector<int>> group_by_remainder(const std::vector<int>& v, int k) {
    std::vector<std::vector<int>> res(k);
    for (int x : v) {
        int r = (x % k + k) % k;
        res[r].push_back(x);
    }
    return res;
}