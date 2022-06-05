/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:02:47 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/31 12:31:43 by kpucylo          ###   ########.fr       */
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
}

#endif
