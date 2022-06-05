/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:51 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/31 15:07:19 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "utils.hpp"
#include "random_access_iterator.hpp"

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
		typedef typename ft::random_access_iterator<const T> const_iterataor;
		typedef typename allocator_type::size_type size_type;

		//constructors to be implemented
		//default constructor
		explicit vector(const allocator_type &alloc = allocator_type());
		//fills n elements with value val
		explicit vector(size_type n, const value_type &val = value_type(), \
			const allocator_type &alloc = allocator_type());
	};
}

#endif
