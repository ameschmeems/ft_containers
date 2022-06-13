/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:34:39 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/13 15:41:39 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "rbt_iterator.hpp"
#include "rbt.hpp"
#include "utils.hpp"

//TBD: destructor clean-up, object's iterators, look into max_size

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename RBT_Iterator<key_type, mapped_type, false> iterator;
		typedef typename RBT_Iterator<key_type, mapped_type, true> const_iterator;
		typedef typename reverse_iterator<iterator> reverse_iterator;
		typedef typename reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		class value_compare
		{
		public:

			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const
			{
				return (comp(x.first, y.first));
			}

		protected:

			Compare comp;
			value_compare(Compare c) : comp(c) {}

		private:

			friend class map;
		};

		explicit map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type()) : _tree() {}
		
		template <class InputIterator>
		map(InputIterator first, InputIterator second, const key_compare &comp = key_compare,
			const allocator_type &alloc = allocator_type()) : _tree()
		{
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		map(const map &copy) : _tree()
		{
			*this = copy;
		}

		~map(void)
		{
			this->clear();
			//deallocate or sth?? (or do this in RBT destructor actually)
		}

		map &operator=(const map &rhs)
		{
			iterator first = rhs.begin();
			iterator last = rhs.end();
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		//too tired to think, and i havent implemented a way to get those from tree yet
		iterator begin(void);
		const_iterator begin(void) const;
		iterator end(void);
		const_iterator end(void) const;
		reverse_iterator rbegin(void);
		const_reverse_iterator rbegin(void) const;
		reverse_iterator rend(void);
		const_reverse_iterator rend(void) const;

		bool empty(void) const
		{
			return (this->_tree.empty());
		}

		size_type size(void) const
		{
			return (this->_tree.size());
		}

		//dont know yet
		size_type max_size(void) const;

		mapped_type &operator[](const key_type &key)
		{
			return ((*((this->insert(make_pair(k, mapped_type()))).first)).second);
		}

		

	private:

		RBT _tree;
	};
}

#endif