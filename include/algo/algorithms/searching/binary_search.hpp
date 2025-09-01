#pragma once
#include <vector>
#include <optional>

namespace algo::search {
	
	template <typename T>
	std::optional<size_t> binary_search_iter(const std::vector<T>& arr, const T& target) noexcept {
		size_t left = 0;
		size_t right = arr.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (arr[mid] == target) return mid;
			if (arr[mid] < target) left = mid + 1;
			else right = mid;
		}

		return std::nullopt;
	}

} // namespace algo::search