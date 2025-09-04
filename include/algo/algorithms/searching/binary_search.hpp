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

	template <typename T>
	std::optional<size_t> binary_search_rec(const std::vector<T>& arr, size_t left, size_t right, const T& target) noexcept {
		if (left > right) return std::nullopt;

		size_t mid = left + (right - left) / 2;
		if (arr[mid] == target) return mid;
		if (arr[mid] < target) return binary_search_rec(arr, mid + 1, right, target);
		else return binary_search_rec(arr, left, mid - 1, target);
	}

} // namespace algo::search