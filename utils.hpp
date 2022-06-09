/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:02:47 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/08 14:07:18 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <stddef.h>

namespace ft
{
	//base iterator class
	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	class iterator
	{
	public:

		//type of elements pointed to
		typedef T value_type;
		//represents difference between two iterators
		typedef Distance difference_type;
		//pointer to element pointed to
		typedef Pointer pointer;
		//reference to element pointed to
		typedef Reference reference;
		//category of the iterator
		typedef Category iterator_category;
	};

	//empty class to identify random_access_iterator
	class random_access_iterator_tag {};

	//struct defining iterator properties, taken from Iterator class
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	//reverse iterator to given Iterator class
	template <class Iterator>
	class reverse_iterator
	{
	public:

		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

		reverse_iterator(void) : _element(NULL) {}
		explicit reverse_iterator(iterator_type it) : _element(it) {}
		template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it)
				: _element(rev_it.base()) {}
		virtual ~reverse_iterator(void) {}

		iterator_type base(void) const
		{
			return (this->_element);
		}

		reference operator*(void) const
		{
			iterator temp = this->_element;
			temp--;
			return (*temp);
		}
		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->_element - n));
		}
		reverse_iterator &operator++(void)
		{
			this->_element--;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return (temp);
		}
		reverse_iterator &operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		}
		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->_element + n));
		}
		reverse_iterator &operator--(void)
		{
			this->_element++;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return (temp);
		}
		reverse_iterator &operator-=(difference_type n)
		{
			*this = *this - n;
		}
		pointer operator->(void) const
		{
			return(&(operator*()));
		}
		reference operator[](difference_type n) const
		{
			return (this->base()[-n - 1]);
		}

	private:

		pointer _element;
	};
	//non-member overloads for reverse_iterator
	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator==(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator!=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator<(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator<=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator>(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template<class Iterator_L, class Iterator_R>
	bool operator>=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs,
																const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	//convert n to std::string
	template<typename T>
	std::string to_str(T n)
	{
		std::ostringstream oss;
		oss << n;
		return (oss.str());
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			first++;
			n++;
		}
		return (n);
	}
}

#endif
