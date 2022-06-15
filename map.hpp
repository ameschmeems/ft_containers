/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:34:39 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/15 19:48:12 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "rbt_iterator.hpp"
#include "rbt.hpp"
#include "utils.hpp"

//TBD: figure out reverse_iterator, do someting about insert with iterator hint

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
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
	
	private:

		typedef RBT<key_type, mapped_type, allocator_type> tree_type;

	public:

		typedef RBT_Iterator <tree_type::node, tree_type> iterator;
		typedef const_RBT_Iterator <tree_type::node, tree_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iteratator;
	
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
					const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}
		
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr) : _tree(comp, alloc)
		{
			while (first != second)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		map(const map &x) : _tree()
		{
			*this = x;
		}

		~map(void)
		{
			this->clear();
		}

		map &operator=(const map &x)
		{
			this->clear();
			iterator first = x.begin();
			iterator last = x.end();
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		iterator begin(void)
		{
			return (this->_tree.begin());
		}

		const_iterator begin(void) const
		{
			return (this->_tree.cbegin());
		}

		iterator end(void)
		{
			return (this->_tree.end());
		}

		const_iterator end(void)
		{
			return (this->_tree.cend());
		}

		bool empty(void) const
		{
			return (this->_tree.empty());
		}

		size_type size(void) const
		{
			return (this->_tree.size());
		}

		size_type max_size(void) const
		{
			return (this->_tree.max_size());
		}

		mapped_type &operator[]
		{
			return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			tree_type::node *n = this->_tree.find(val->first);
			if (n == nullptr)
			{
				n = this->_tree.insert(val);
				return (ft::make_pair(iterator(n, this->_tree.getNil()), true));
			}
			return (ft::make_pair(iterator(n, this->_tree.getNil()), false));
		}

		iterator insert(iterator position, const value_type &val)
		{
			return (iterator(this->_tree.insert(val), this->_tree.getNil()));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr)
		{
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			this->_tree.erase((*position).first);
		}

		size_type erase(const key_type &key)
		{
			return (this->_tree.erase(key));
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->_tree.erase((*first).first);
				first++;
			}
		}

		void swap(map &x)
		{
			map<key_type, mapped_type, key_compare, allocator_type> temp(x);
			x.clear();
			x = *this;
			this->clear();
			*this = temp;
		}

		void clear(void)
		{
			iterator first = this->begin();
			while (first != this->end())
			{
				this->erase(first);
				first++;
			}
		}

	private:

		tree_type _tree;
	};
}

#endif