#pragma once

#include <vector>
#include <stdexcept>

int sum(const std::vector<int>& v);

std::vector<int> filter_even(const std::vector<int>& v);

void rotate_left(std::vector<int>& v, std::size_t k);

std::vector<int> remove_duplicates(const std::vector<int>& v);

std::vector<int> flatten(const std::vector<std::vector<int>>& matrix);

std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b);

int max_subarray_sum(const std::vector<int>& v);

std::vector<std::vector<int>> group_by_remainder(const std::vector<int>& v, int k);
