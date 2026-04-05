#include "tasks.h"
#include <stdexcept>

int sum(const std::vector<int>& v) {
    int result = 0;
    for (int x : v) {
        result += x;
    }
    return result;
}

std::vector<int> filter_even(const std::vector<int>& v) {
    std::vector<int> result;
    for (int x : v) {
        if (x % 2 == 0) {
            result.push_back(x);
        }
    }
    return result;
}

void rotate_left(std::vector<int>& v, std::size_t k) {
    if (v.empty()) {
        return;
    }

    k %= v.size();
    std::vector<int> result;

    for (std::size_t i = k; i < v.size(); ++i) {
        result.push_back(v[i]);
    }

    for (std::size_t i = 0; i < k; ++i) {
        result.push_back(v[i]);
    }

    v = result;
}

std::vector<int> remove_duplicates(const std::vector<int>& v) {
    std::vector<int> result;

    for (int x : v) {
        bool found = false;

        for (int y : result) {
            if (x == y) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(x);
        }
    }

    return result;
}

std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> result;

    for (const auto& row : matrix) {
        for (int x : row) {
            result.push_back(x);
        }
    }

    return result;
}

std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    std::size_t i = 0;
    std::size_t j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            result.push_back(a[i]);
            ++i;
        } else {
            result.push_back(b[j]);
            ++j;
        }
    }

    while (i < a.size()) {
        result.push_back(a[i]);
        ++i;
    }

    while (j < b.size()) {
        result.push_back(b[j]);
        ++j;
    }

    return result;
}

int max_subarray_sum(const std::vector<int>& v) {
    if (v.empty()) {
        throw std::invalid_argument("empty vector");
    }

    int current = v[0];
    int best = v[0];

    for (std::size_t i = 1; i < v.size(); ++i) {
        if (current + v[i] > v[i]) {
            current = current + v[i];
        } else {
            current = v[i];
        }

        if (current > best) {
            best = current;
        }
    }

    return best;
}

std::vector<std::vector<int>> group_by_remainder(const std::vector<int>& v, int k) {
    if (k <= 0) {
        throw std::invalid_argument("k must be positive");
    }

    std::vector<std::vector<int>> result(k);

    for (int x : v) {
        int remainder = (x % k + k) % k;
        result[remainder].push_back(x);
    }

    return result;
}