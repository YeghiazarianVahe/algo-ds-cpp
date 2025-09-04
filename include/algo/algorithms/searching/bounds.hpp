#pragma once
#include <vector>

namespace algo::search {

	template <typename T>
	size_t lower_bound(const std::vector<T>& arr, const T& target) noexcept {
		size_t left = 0;
		size_t right = arr.size();

		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (arr[mid] < target) left = mid + 1;
			else right = mid;
		}

		return left;
	}

	template <typename T>
	size_t upper_bound(const std::vector<T>& arr, const T& target) noexcept {
		size_t left = 0;
		size_t right = arr.size();

		while (left < right) {
			size_t mid = left + (right - left) / 2;

			if (arr[mid] <= target) {
				left = mid + 1; 
			}
			else {
				right = mid;
			}
		}

		return left;
	}

} // namespace algo::search