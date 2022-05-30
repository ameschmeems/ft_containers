/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:02:47 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/30 15:41:11 by kpucylo          ###   ########.fr       */
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
}

#endif
