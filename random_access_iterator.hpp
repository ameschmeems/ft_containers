/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:37:26 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/31 15:04:16 by kpucylo          ###   ########.fr       */
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

		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

		//default constructor
		random_access_iterator(void) : _element(NULL) {}
		//copy constructor
		random_access_iterator(const random_access_iterator &copy) : _element(copy._element) {}
		//pointer constructor
		random_access_iterator(pointer element) : _element(element) {}
		//default destructor
		virtual ~random_access_iterator(void) {}
		//copy assignment operator
		random_access_iterator &operator=(const random_access_iterator &it)
		{
			this->_element = it.element;
			return (*this);
		}
		//return current pointer
		pointer base(void) const
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
			return (&(this->operator*()));
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
		//subtraction/addition
		random_access_iterator operator+(differnece_type n) const
		{
			return (this->_element + n);
		}
		random_access_iterator operator-(difference_type n) const
		{
			return (this->_element - n);
		}
		random_access_iterator &operator+=(difference_type n)
		{
			this->_element += n;
			return (*this);
		}
		random_access_iterator &operator-=(difference_type n)
		{
			this->_element -= n;
			return (*this);
		}
		reference operator[](difference_type n)
		{
			return (*(this->_element + n));
		}

	private:

		//element pointed to by iterator
		pointer _element;
	};

	//logical operators
	template<typename T>
	bool operator==(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator==(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T>
	bool operator!=(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator!=(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T>
	bool operator>(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator>(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T>
	bool operator>=(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator>=(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	bool operator<(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator<(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T>
	bool operator<=(const random_access_iterator<T> &lhs,
					const random_access_iterator<T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	//for comparing with const iterators
	template<typename T_L, typename T_R>
	bool operator<=(const random_access_iterator<T_L> &lhs,
					const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	//adding difference_type with iterator
	template<typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
										random_access_iterator<T> &it)
	{
		return (&(*it) + n);
	}

	//returns difference between two iterators
	template<typename T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs,
																const random_access_iterator<T> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	//for difference with const_iterators
	template<typename T_L, typename T_R>
	typename random_access_iterator<T_L>::difference_type operator-(const random_access_iterator<T_L> &lhs,
																const random_access_iterator<T_R> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
