/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:37:26 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/31 15:02:06 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	//allows for iterating at any point of the container
	template<typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:

		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef T* pointer;
		typedef T& reference;

		//default constructor
		random_access_iterator(void) : _element(NULL) {}
		//copy constructor
		random_access_iterator(const random_access_iterator &copy) : _element(copy._element) {}
		//default destructor
		~random_access_iterator(void) {}
		//copy assignment operator
		random_access_iterator &operator=(const random_access_iterator &it)
		{
			this->_element = it.element;
			return (*this);
		}
		//return current pointer
		pointer base() const
		{
			return (this->_element);
		}
		//dereference current pointer
		reference operator*(void) const
		{
			return (*(this->_element));
		}
		//member access operator
		pointer operator->(void)
		{
			return (this->_element);
		}
		//logical operators
		bool operator==(const random_access_iterator &it)
		{
			return (this->_element == it._element);
		}
		bool operator!=(const random_access_iterator &it)
		{
			return (this->_element != it._element);
		}
		bool operator<(const random_access_iterator &it)
		{
			return (this->_element < it._element);
		}
		bool operator<=(const random_access_iterator &it)
		{
			return (this->_element <= it._element);
		}
		bool operator>(const random_access_iterator &it)
		{
			return (this->_element > it._element);
		}
		bool operator>=(const random_access_iterator &it)
		{
			return (this->_element >= it._element);
		}
		//pre/post increments and decrements
		random_access_iterator operator++(int)
		{
			random_access_iterator temp = *this;
			this->_element++;
			return (temp);
		}
		random_access_iterator &operator++(void)
		{
			this->_element++;
			return (*this);
		}
		random_access_iterator operator--(int)
		{
			random_access_iterator temp = *this;
			this->_element--;
			return (temp);
		}
		random_access_iterator &operator--(void)
		{
			this->_element--;
			return (*this);
		}
		//subtraction/addition with iterators or ints
		random_access_iterator operator+(const random_access_iterator &it) const
		{
			random_access_iterator retval(*this);
			retval->_element += it._element;
			return (retval);
		}
		random_access_iterator operator+(const int i) const
		{
			random_access_iterator retval(*this);
			retval->_element += i;
			return (retval);
		}
		random_access_iterator operator-(const random_access_iterator &it) const
		{
			random_access_iterator retval(*this);
			retval->_element -= it._element;
			return (retval);
		}
		random_access_iterator operator-(const int i) const
		{
			random_access_iterator retval(*this);
			retval->_element -= i;
			return (retval);
		}
		random_access_iterator &operator+=(const random_access_iterator &it)
		{
			*this = *this + it;
			return (*this);
		}
		random_access_iterator &operator-=(const int i)
		{
			*this = *this + i;
			return (*this);
		}
		reference operator[](difference_type i)
		{
			return (*(_element + i));
		}

	private:

		//element pointed to by iterator
		pointer _element;
	};
}

#endif
