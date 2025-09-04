#pragma once
#include <optional>
#include <vector>

namespace algo::search {
	
	template <typename T>
	std::optional<size_t> first_occurrence(const std::vector<T>& arr, const T& target) noexcept {
		size_t left = 0;
		size_t right = arr.size();

		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (arr[mid] < target) left = mid + 1;
			else right = mid;
		}

		if (left < arr.size() && arr[left] == target) return left;
		return std::nullopt;
	}

	template <typename T>
	std::optional<size_t> last_occurrence(const std::vector<T>& arr, const T& target) noexcept {
		size_t left = 0;
		size_t right = arr.size();

		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (arr[mid] < target) left = mid + 1;
			else right = mid;
		}

		if (left > 0 && arr[left - 1] == target) return left - 1;
		return std::nullopt;
	}

} // namespace algo:search