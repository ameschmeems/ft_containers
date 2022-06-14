/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:34:39 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/14 14:23:10 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "rbt_iterator.hpp"
#include "rbt.hpp"
#include "utils.hpp"

//TBD: i need to test shit, but iterator end should probably get _nil ptr instead of NULL

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
					const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator second, const key_compare &comp = key_compare,
			const allocator_type &alloc = allocator_type(),
			typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr) : _tree(comp, alloc)
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
		}

		map &operator=(const map &rhs)
		{
			this->clear();
			iterator first = rhs.begin();
			iterator last = rhs.end();
			while (first != last)
			{
				this->_tree.insert(*first);
				first++;
			}
			return (*this);
		}

		iterator begin(void)
		{
			return (iterator(this->_tree.begin(), this->_tree.begin(), this->_tree.rbegin()));
		}

		const_iterator begin(void) const
		{
			return (const_iterator(this->_tree.begin(), this->_tree.begin(), this->_tree.rbegin()));
		}

		iterator end(void)
		{
			return (iterator(NULL, this->_tree.begin(), this->_tree.rbegin()));
		}

		const_iterator end(void) const
		{
			return (const_iterator(NULL, this->_tree.begin(), this->_tree.rbegin()));
		}

		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(iterator(this->_tree.rbegin(), this->_tree.begin(), this->_tree.rbegin())));
		}

		const_reverse_iterator rbegin(void) const
		{
			return (const_reverse_iterator(const_iterator(this->_tree.rbegin(), this->_tree.begin(), this->_tree.rbegin())));
		}

		reverse_iterator rend(void)
		{
			return (reverse_iterator(iterator(NULL, this->_tree.begin(), this->_tree.rbegin())));
		}

		const_reverse_iterator rend(void) const
		{
			return (const_reverse_iterator(const_iterator(NULL, this->_tree.begin(), this->_tree.rbegin())));
		}

		bool empty(void) const
		{
			return (this->_tree.empty());
		}

		size_type size(void) const
		{
			return (this->_tree.size());
		}

		//dont know yet
		size_type max_size(void) const
		{
			return (this->_tree.max_size());
		}

		mapped_type &operator[](const key_type &key)
		{
			return ((*((this->insert(make_pair(k, mapped_type()))).first)).second);
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			iterator it(this->find(val.first));

			if (it != iterator())
				return (make_pair(it, false));
			it = iterator(this->_tree.insert(val));
			return (make_pair(it, true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			if (pos != iterator())
				return (this->_tree.insert(val));
			return (iterator());
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

		void erase(iterator pos)
		{
			this->_tree.erase((*pos).first);
		}

		size_type erase(const key_type &key)
		{
			return (this->_tree.erase(key));
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->_tree.erase(first);
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
			iterator it = this->begin();
			while (it != this->end())
			{
				this->erase(*it);
				it++;
			}
		}

		key_compare key_comp(void) const
		{
			return (this->_tree.get_comp());
		}

		value_compare value_comp(void) const
		{
			return (value_compare(this->_tree.get_comp()));
		}

		iterator find(const key_type &key)
		{
			return (this->_tree.find(key));
		}

		const_iterator find(const key_type &key) const
		{
			return (this->_tree.find(key));
		}

		size_type count(const key_type &key) const
		{
			if (this->_tree.find(key))
				return (1);
			return (0);
		}

		iterator lower_bound(const key_type &key)
		{
			iterator it = this->begin();
			while (it != this->end() && (this->_tree.get_comp())((*it).first, key))
				it++;
			return (it);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator it = this->begin();
			while (it != this->end() && (this->_tree.get_comp())((*it).first, key))
				it++;
			return (it);
		}

		iterator upper_bound(const key_type &key)
		{
			iterator it = this->begin();
			while (it != this->end() && !((this->_tree.get_comp())(key, (*it).first)))
				it++;
			return (it);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator it = this->begin();
			while (it != this->end() && !((this->_tree.get_comp())(key, (*it).first)))
				it++;
			return (it);
		}

		pair<iterator, iterator> equal_range(const key_type &key)
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}

		allocator_type get_allocator(void) const
		{
			return (this->_tree.get_allocator());
		}

	private:

		RBT<key_type, mapped_type, allocator_type> _tree;
	};
}

#endif