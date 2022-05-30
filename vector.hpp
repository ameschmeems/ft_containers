/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:51 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/30 15:40:46 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "utils.hpp"

namespace ft
{
	//allows for iterating at any point of the container
	template<typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:

		//default constructor
		random_access_iterator(void);
		//copy constructor
		random_access_iterator(const random_access_iterator &copy);
		//default destructor
		~random_access_iterator(void);
		//copy assignment operator
		random_access_iterator &operator=(const random_access_iterator &it);
	};

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
		typedef typename allocator_type::size_type size_type;

		//constructors to be implemented
		//default constructor
		explicit vector(const allocator_type &alloc = allocator_type());
		//fills n elements with value val
		explicit vector(size_type n, const value_type &val = value_type(), \
			const allocator__type &alloc = allocator_type());
	};
}

#endif
