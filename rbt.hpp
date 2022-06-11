/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:52:43 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/11 16:52:43 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <memory>
#include "utils.hpp"

namespace ft
{
	template <typename Key, typename T, typename Alloc = std::allocator<pair<const Key, T> > >
	class RBT
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;

	private:
	};
}

#endif