#ifndef MESA_CISC187_BAG
#define MESA_CISC187_BAG

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace mesa {
	template<typename T>
	class bag {
	private:
		size_t _size, _capacity;
		T* _data;

	public:
		typedef T value_type;

		bag(size_t size = 0): _size(size), _capacity(size) {

			if (_size != 0) {
				_data = new T[_size];
				std::fill(_data, _data + _size, T());
			}
			else _data = nullptr;
		}

		bag(std::initializer_list<T> list): _size(list.size()),
			_capacity(list.size()), _data(new T[list.size()]) {

			std::copy(list.begin(), list.end(), _data);
		}

		bag(const bag<T>& src): _size(src._size),
			_capacity(src._capacity), _data(new T[_size]) {

			std::copy(src.begin(), src.end(), _data);
		}

		bag(bag<T>&& src) noexcept: _size(src._size),
			_capacity(src._capacity), _data(src._data) {
			src._data = nullptr;
		}

		bag<T>& operator=(const bag<T>& src) {

			bag<T> copy(src);
			std::swap(_data, copy._data);
			_capacity = copy._capacity;
			_size = copy._size;

			return *this;
		}

		bag<T>& operator=(bag<T>&& src) noexcept {

			std::swap(_data, src._data);
			_capacity = src._capacity;
			_size = src._size;

			return *this;
		}

		const size_t capacity() const noexcept { return _capacity; }

		const size_t size() const noexcept {return _size;}

		void reserve(size_t new_capacity) {
			if (new_capacity > _capacity) {

				T* temp = new T[new_capacity];
				std::copy(_data, _data + _capacity, temp);

				delete[] _data;
				_data = temp;
				_capacity = new_capacity;
			}
		}

		void resize(size_t new_capacity) {
			reserve(new_capacity);
			if (new_capacity > _size) {
				std::fill(_data + _size, _data + new_capacity, T());
			}
			_size = new_capacity;
		}

		void push_back(T value) {
			if (_size == _capacity) {
				reserve(std::max(2 * _size, (size_t)1));
			}
			_data[_size] = value;
			_size++;
		}

		void pop_back() {
			_size = (_size > 0) ? (_size - 1) : 0;
		}

		constexpr T& operator[](size_t index) {
			return _data[index];
		}

		constexpr const T& operator[](size_t index) const {
			return _data[index];
		}

		constexpr const T& at(size_t index) const {
			if (index >= _size || index < 0) {
				throw std::out_of_range("bag<T>::at(): index is out of range");
			}
			return _data[index];
		}

		constexpr T& at(size_t index) {
			if (index >= _size || index < 0) {
				throw std::out_of_range("bag<T>::at(): index is out of range");
			}
			return _data[index];
		}

		T* data() {
			return _data;
		}

		constexpr const T* data() const {
			return _data;
		}

		T& back() {
			return _data[_size-1];
		}

		constexpr const T& back() const {
			return _data[_size-1];
		}

		constexpr T* begin() noexcept {
			return _data;
		}
		constexpr T* end() noexcept {
			return _data + _size;
		}

		constexpr const T* begin() const noexcept {
			return _data;
		}
		constexpr const T* end() const noexcept {
			return _data + _size;
		}

		constexpr bool empty() const noexcept {
			return _size == 0;
		}

		void print() {
			for (const auto& e : _data) {
				std::cout << e << " ";
			}
		}

		~bag() {
			delete[] _data;
		}
	};

	template <typename T>
	inline bool operator==(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	inline bool operator!=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	inline bool operator<(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	inline bool operator>=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs < rhs);
	}

	template <typename T>
	inline bool operator>(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::lexicographical_compare(
			rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <typename T>
	inline bool operator<=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs < rhs);
	}
}
#endif