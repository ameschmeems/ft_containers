/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:51 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/10 13:48:28 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "utils.hpp"
#include "random_access_iterator.hpp"

//TBD: modify with enable_if once implemented

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::random_access_iterator<T> iterator;
		typedef typename ft::random_access_iterator<const T> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::size_type size_type;

		//constructors to be implemented
		//default constructor
		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _capacity(nullptr) {}

		//fills n elements with value val
		explicit vector(size_type n, const value_type &val = value_type(), \
			const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _capacity(nullptr)
		{
			_start = _alloc.allocate(n);
			_capacity = _start + n;
			_end = _start;
			while (n--)
			{
				_alloc.construct(_end, val);
				_end++;
			}
		}

		//constructs vectro with elements from between two iterators
		template<class InputIterator>
		vector(InputIterator first, InputIterator last, \
				const allocator_type &alloc = allocator_type()) : _alloc(alloc)
		{
			difference_type n = ft::distance(first, last);
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_capacity = this->_start + n;
			while (n--)
			{
				this->_alloc.construct(this->_end, *first);
				first++;
				this->_end--;
			}
		}

		vector(const vector &x) : _alloc(x._alloc), _start(nullptr), _end(nullptr), _capacity(nullptr)
		{
			this->insert(this->begin(), x.begin(), x.end());
		}

		//destroy all elements and dealloc memory
		~vector(void)
		{
			this->clear();
			this-_alloc.deallocate(this->_start, this->capacity());
		}

		vector &operator=(const vector &x)
		{
			if (x == *this)
				return (*this);
			this->clear();
			this->insert(this->end(), x.begin(), x.end());
			return (*this);
		}

		iterator begin(void)
		{
			return (this->_start);
		}

		const_iterator begin(void) const
		{
			return (this->_start);
		}

		iterator end(void)
		{
			if (this->empty())
				return (this->begin());
			return (this->_end);
		}

		const_iterator end(void) const
		{
			if (this->empty())
				return (this->begin());
			return (this->_end);
		}

		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator rbegin(void) const
		{
			return (reverse_iterator(this->end()));
		}

		reverse_iterator rend(void)
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rend(void) const
		{
			return (reverse_iterator(this->begin()));
		}

		//returns number of elements stored
		size_type size(void) const
		{
			return (this->_end - this->start);
		}

		//returns max possible size for the vector
		size_type max_size(void) const
		{
			return (allocator_type().max_size);
		}

		//resizes vector to fit n elements
		//if n is smaller than actual size, shrinks the container to n
		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("vector::resize");
			else if (n < this->size())
			{
				while (this->size() > n)
				{
					this->_end--;
					this->_alloc.destroy(this->_end);
				}
			}
			else
				this->insert(this->end(), n - this->size(), val);
		}

		//returns allocated size
		size_type capacity(void) const
		{
			return (this->_capacity - this->_start);
		}

		//returns true if vector is empty
		bool empty(void) const
		{
			if (this->size() == 0)
				return (true);
			return (false);
		}

		//if vector has less capacity than end, expands to fit at least n elements
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			else if (n > this->capacity())
			{
				pointer prev_start = this->_start;
				pointer prev_end = this->_end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				this->_start = this->_alloc.allocate(n);
				this->_capacity = this->_start + n;
				this->_end = this->_start;
				while (prev_start != prev_end)
				{
					this->_alloc.construct(this->_end, *prev_start);
					this->_end++;
					prev_start++;
				}
				this->_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		//returns reference to element at nth position
		reference operator[](size_type n)
		{
			return (*(this->_start + n));
		}

		const_reference operator[](size_type n) const
		{
			return (*(this->_start + n));
		}

		//same as operator[], but throws an exception if element is out of range
		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("vector::at: n == " + ft::to_str(n)
										+ " is bigger than vector size == ", ft::to_str(this->size()));
			return ((*this)[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("vector::at: n == " + ft::to_str(n)
										+ " is bigger than vector size == ", ft::to_str(this->size()));
			return ((*this)[n]);
		}

		//returns reference to first element (on empty container undefined behavior)
		reference front(void)
		{
			return (*this->_start);
		}

		const_reference front(void) const
		{
			return (*this->_start);
		}

		//returns reference to the last element (on empty container undefined behavior)
		reference back(void)
		{
			return (*(this->_end - 1));
		}

		const_reference back(void) const
		{
			return (*(this->_end - 1));
		}

		//replaces vector contents with ones taken from range between iterators
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			this->clear();
			size_type dist = ft::distance(first, last);
			if (size_type(this->_capacity - this->_start) >= dist)
			{
				while (first != last)
				{
					this->_alloc.construct(this->_end, *first);
					first++;
					this->_end++;
				}
			}
			else
			{
				pointer new_start = this->_alloc.allocate(dist);
				pointer new_end = new_start;
				pointer new_capacity = new_start + dist;
				while (first != last)
				{
					this->_alloc.construct(new_end, *first);
					first++;
					new_end++;
				}
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		//replace container elements with n elements of value val
		void assign(size_type n, const value_type &val)
		{
			this->clear();
			if (n == 0)
				return ;
			if (size_type(this->_capacity - this->_start) >= n)
			{
				while (n)
				{
					this->_alloc.construct(this->_end, val);
					n--;
					this->_end++;
				}
			}
			else
			{
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_capacity = this->_start + n;
				while (n)
				{
					this->_alloc.construct(this->_end, val);
					n--;
					this->_end++;
				}
			}
		}

		//add new element at the end of vector
		void push_back(const value_type &val)
		{
			if (this->_end == this->_capacity)
			{
				int new_capacity;
				if (this->size() == 0)
					new_capacity = 1;
				else
					new_capacity = this->size() * 2;
				this->reserve(new_capacity);
			}
			this->_alloc.construct(this->_end, val);
			this->_end++;
		}

		//remove element from the back
		void pop_back(void)
		{
			this->_alloc.destroy(&(this->back()));
			this->_end--;
		}

		//inserts element val at speciied position, moving the next elements
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = &(*position) - this->_start;
			if (size_type(this->_capacity - this->_end) >= this->size() + 1)
			{
				for (size_type i = 0; i < pos; i++)
					this->_alloc.construct(this->_end - i, *(this->_end - i - 1));
				this->_end++;
				this->_alloc.construct(&(*position), val);
			}
			else
			{
				int new_capacity;
				if (this->size() == 0)
					new_capacity = 1;
				else
					new_capacity = this->size() * 2;
				pointer new_start = this->_alloc.allocate(new_capacity);
				pointer new_end = new_start + this->size() + 1;
				pointer new_capacity_ptr = new_start + new_capacity;
				for (size_type i = 0; i < pos; i++)
					this->_alloc.construct(new_start + i, *(this->_start + i));
				this->_alloc.construct(new_start + pos, val);
				for (size_type j = 0; j < this->size() - pos; j++)
					this->_alloc.construct(new_end - j - 1, *(this->_end - j - 1));
				for (size_type k = 0; k < this->size(); k++)
					this->_alloc.destroy(this->_start + k);
				if (this->_start)
					this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity_ptr;
			}
			return (iterator(this->_start + pos));
		}

		//insert n elements of value val, at specified position
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::insert");
			size_type pos = &(*position) - this->_start;
			if (size_type(this->_capacity - this->_end) >= n)
			{
				for (size_type i = 0; i < this->size() - pos; i++)
					this->_alloc.construct(this->_end - i + (n - 1), *(this->_end - i - 1))
				this->_end += n;
				while (n)
				{
					this->_alloc.construct(&(*position) + (n - 1), val);
					n--;
				}
			}
			else
			{
				int new_capacity;
				if (this->size() == 0)
					new_capacity = 0;
				else
					new_capacity = this->size() * 2;
				pointer new_start = this->_alloc.allocate(new_capacity);
				pointer new_capacity_ptr = new_start + new_capacity;
				pointer new_end = pointer();
				if (size_type(new_capacity_ptr - new_start) < this->size() + n)
				{
					if (new_start)
						this->_alloc.deallocate(new_start, new_capacity_ptr - new_start);
					new_capacity = this->size() + n;
					new_start = this->_alloc.allocate(new_capacity);
					new_capacity_ptr = new_start + next_capacity;
				}
				new_end = new_start + this->size() + n;
				for (int i = 0; i < (&(*position) - this->_start); i++)
					this->_alloc.construct(new_start + i, *(this->_start + i));
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(new_start + pos + j, val);
				for (size_type k = 0; j < (this->size() - pos); j++)
					this->_alloc.construct(new_end - j - 1, *(this->_end - j - 1));
				for (size_type l = 0; l < this->size(); l++)
					this->_alloc.destroy(this->_start + l);
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity_ptr;
			}
		}

		//insert elements between first and last, starting at specified position
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type n = ft::distance(first, last);
			if (size_type(this->_capacity - this->_end) >= n)
			{
				for (size_type i = 0; i < (this->size() - &(*position) - this->_start); i++)
					this->_alloc.construct(this->_end - i + n - 1, *(this->_end - i - 1));
				this->_end += n;
				while (first != last)
				{
					this->_alloc.construct(&(*position), *first);
					first++;
					position++;
				}
			}
			else
			{
				pointer new_start = this->_alloc.allocate(this->size() * 2);
				pointer new_end = new_start + this->size() + n;
				pointer new_capacity = new_start + (this->size() * 2);
				if (size_type(new_capacity - new_start) < this->size() + n)
				{
					if (new_start)
						this->_alloc.deallocate(new_start, new_capacity - new_start);
					new_start = this->_alloc.allocate(this->size() + n);
					new_end = new_start + this->size() + n;
					new_capacity = new_end;
				}
				for (int i = 0; i < &(*position) - this->_start; i++)
					this->_alloc.construct(new_start + i, (*this->_start + i));
				for (int j = 0; first != last; first++, j++)
					this->_alloc.construct(new_start + (&(*position) - this->_start) + j, *first);
				for (size_type k = 0; k < this->size() - (&(*position) - this->_start); k++)
					this->_alloc.construct(new_start + (&(*position) - this->_start) + n + k, *(&(*position) + k));
				for (size_type l = 0; l < this->size(); l++)
					this->_alloc.destroy(this->_start + l);
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		//erase element at specified position and return iterator to the element after the last erased
		iterator erase(iterator position)
		{
			pointer pos = &(*position);
			this->_alloc.destroy(pos);
			if (&(*position) + 1 != this->_end)
			{
				for (int i = 0; i < this->_end - &(*position) - 1; i++)
				{
					this->_alloc.construct(&(*position) + i, (*(&(*position)) + i + 1));
					this->_alloc.destroy(&(*position) + i + 1);
				}
			}
			this->_end--;
			return (iterator(pos));
		}

		//erases elements in range from first to last
		iterator erase(iterator first, iterator last)
		{
			pointer f_pos = &(*first);
			while (first != last)
			{
				this->_alloc.destroy(&(*first));
				first++;
			}
			for (int i = 0; i < this->_end - &(*last); i++)
			{
				this->_alloc.construct(f_pos + i, *(&(*last) + i));
				this->_alloc.destroy(&(*last) + i);
			}
			this->_end -= &(*last) - f_pos;
			return (iterator(f_pos));
		}

		//swaps vector contents with x
		void swap(vector &x)
		{
			pointer x_start = x._start;
			pointer x_end = x._end;
			pointer x_capacity = x._capacity;
			allocator_type x_alloc = x._alloc;

			x._start = this->_start;
			x._end = this->_end;
			x._capacity = this->_capacity;
			x._alloc = this->_alloc;

			this->_start = x_start;
			this->_end = x_end;
			this->_capacity = x_capacity;
			this->_alloc = x_alloc;
		}

		//destroys all elements in vector, leaving it with size 0
		void clear(void)
		{
			size_type size = this->size();
			for (size_type i = 0; i < size; i++)
			{
				this->_end--;
				this->_alloc.destroy(this->_end);
			}
		}

		//returns vectors allocator
		allocator_type get_allocator(void) const
		{
			return (this->_alloc);
		}

	private:

		allocator_type _alloc;
		//pointer to first element
		pointer _start;
		//pointer to last element
		pointer _end;
		//pointer to end of allocated block
		pointer _capacity;
	};

	//non-member overloads

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
		while (first_l != lhs.end())
		{
			if (*first_l != *first_r || first_r == rhs.end())
				return (false);
			first_l++;
			first_r++;
		}
		return (true);
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs))
	}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs)
	}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template<class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
