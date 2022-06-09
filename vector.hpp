/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:51 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/08 14:09:12 by kpucylo          ###   ########.fr       */
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
			: _alloc(alloc), _start(NULL), _end(NULL), _capacity(NULL) {}

		//fills n elements with value val
		explicit vector(size_type n, const value_type &val = value_type(), \
			const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _start(NULL), _end(NULL), _capacity(NULL)
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

		vector(const vector &x) : _alloc(x._alloc), _start(NULL), _end(NULL), _capacity(NULL)
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

	private:

		allocator_type _alloc;
		//pointer to first element
		pointer _start;
		//pointer to last element
		pointer _end;
		//pointer to end of allocated block
		pointer _capacity;
	};
}

#endif
