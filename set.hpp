/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:21:19 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/18 01:21:19 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "rbt.hpp"
#include "rbt_iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	public:

		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

	private:

		typedef RBT_Set<key_type, key_type, allocator_type, key_compare, key_type> tree_type;

	public:

		typedef RBT_Iterator<typename tree_type::node, tree_type> iterator;
		typedef const_RBT_Iterator<typename tree_type::node, tree_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit set(const key_compare &comp = key_compare(), \
					const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare() \
			const allocator_type &alloc = allocator_type(), \
			typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr) : _tree(comp, alloc)
		{
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
		}

		set(const set &x) : _tree()
		{
			*this = x;
		}

		~set(void)
		{
			this->clear();
			this->_tree.deallocNil();
		}

		set &operator=(const map &x)
		{
			this->clear();
			const_iterator first = x.begin();
			while (first != x.end())
			{
				this->_tree.insert(*first);
				first++;
			}
			return (*this);
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

		const_iterator end(void) const
		{
			return (this->_tree.cend());
		}

		reverse_iterator rbegin(void)
		{
			reverse_iterator temp(this->end());
			return (temp);
		}

		const_reverse_iterator rbegin(void) const
		{
			const_reverse_iterator temp(this->end());
			return (temp);
		}

		reverse_iterator rend(void)
		{
			reverse_iterator temp(this->begin());
			return (temp);
		}

		const_reverse_iterator rend(void) const
		{
			const_reverse_iterator temp(this->begin());
			return (temp);
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

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			typename tree_type::node *n = this->_tree.find(val);
			if (n == this->_tree.getNil())
			{
				n = this->_tree.insert(val);
				return (ft::make_pair(iterator(n, this->_tree.getNil()), true));
			}
			return (ft::make_pair(iterator(n, this->_tree.getNil()), false));
		}

		iterator insert(iterator position, const value_type &val)
		{
			static_cast<void>(position);
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
			this->_tree.erase(*position);
		}

		size_type erase(const key_type &key)
		{
			return (this->_tree.erase(key));
		}

		void erase(iterator first, iterator last)
		{
			iterator temp = first;
			while (first != last)
			{
				first++;
				this->erase(*temp);
				temp = first;
			}
		}

		void swap(set &x)
		{
			tree_type temp = x._tree;
			x._tree = this->_tree;
			this->_tree = temp;
		}

		void clear(void)
		{
			iterator first = this->begin();
			while (first != this->end())
			{
				this->erase(first);
				first = this->begin();
			}
		}

		key_compare key_comp(void) const
		{
			return (this->_tree.get_comp());
		}

		value_compare value_comp(void) const
		{
			return (this->_tree.get_comp());
		}

		iterator find(const value_type &val) const
		{
			return (iterator(this->_tree.insert(val), this->_tree.getNil()));
		}

		size_type count(const value_type &val)
		{
			if (this->_tree.find(val) != this->_tree.getNil())
				return (1);
			return (0);
		}

		iterator lower_bound(const value_type &val) const
		{
			iterator it = this->begin();
			while (it != this->end() && (this->_tree.get_comp())((*it), key))
				it++;
			return (it);
		}

		iterator upper_bound(const value_type &val) const
		{
			iterator it = this->begin();
			while (it != this->end() && !((this->_tree.get_comp())(key, (*it))))
				it++;
			return (it);
		}

		pair<iterator, iterator> equal_range(const value_type &val) const
		{
			return (ft::make_pair(lower_bound(val), upper_bound(val)));
		}

		allocator_type get_allocator(void) const
		{
			return (this->_tree.get_allocator());
		}

	private:

		tree_type _tree;
	};
}

#endif