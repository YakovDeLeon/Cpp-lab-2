#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

template<typename T>
bool compare(const T a, const T b)
{
	return a < b;
}
template<>
bool compare<const char*>(const char * a, const char * b)
{
	return strcmp(a, b) < 0;
}



template<typename T>
void msort(T arr[], size_t size)
{
	if (size > 1)
	{
		size_t const left_size = size / 2;
		size_t const right_size = size - left_size;
		msort(&arr[0], left_size);
		msort(&arr[left_size], right_size);
		T * tmp_arr = new T[size];
		size_t lidx = 0, ridx = left_size, idx = 0;
		while (lidx < left_size || ridx < size)
		{
			if (compare(arr[lidx], arr[ridx]))
			{
				tmp_arr[idx++] = std::move(arr[lidx]);
				lidx++;
			}
			else
			{
				tmp_arr[idx++] = std::move(arr[ridx]);
				ridx++;
			}
			if (lidx == left_size)
			{
				std::copy(std::make_move_iterator(&arr[ridx]),
					std::make_move_iterator(&arr[size]),
					&tmp_arr[idx]);
				break;
			}
			if (ridx == size)
			{
				std::copy(std::make_move_iterator(&arr[lidx]),
					std::make_move_iterator(&arr[left_size]),
					&tmp_arr[idx]);
				break;
			}
		}
		std::copy(std::make_move_iterator(tmp_arr),
			std::make_move_iterator(&tmp_arr[size]),
			arr);
		delete[] tmp_arr;
	}
}
