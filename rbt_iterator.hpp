/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:22:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/13 13:38:39 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "utils.hpp"
#include "rbt.hpp"

namespace ft
{
	//this exists so i dont have to re-write the entire thing for const_iterator
	template <bool is_const, class isTrue, class isFalse>
	struct choose;

	template <class isTrue, class isFalse>
	struct choose<true, isTrue, isFalse>
	{
		typedef isTrue type;
	};

	template <class isTrue, class isFalse>
	struct choose<false, isTrue, isFalse>
	{
		typedef isFalse type;
	};

	template <typename Key, typename T, bool is_const>
	class RBT_Iterator : public iterator<bidirectional_iterator_tag, T>
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		RBT_Iterator(void) : _first(nullptr), _last(nullptr), _ptr(nullptr) {}

		RBT_Iterator(node_type ptr, node_type first = nullptr, node_type last = nullptr)
			: _ptr(ptr), _first(first), _last(last) {}

		~RBT_Iterator(void) {}

		template <typename U, typename V, bool const_val>
		RBT_Iterator(const RBT_Iterator<U, V, const_val) : _p(r.getPtr()) {}

		RBT_Iterator &operator=(const RBT_Iterator &rhs)
		{
			this->_ptr = rhs._ptr;
			this->_first = rhs._first;
			this->_last = rhs._last;
			return (*this);
		}

		node_type getPtr(void) const
		{
			return (this->_ptr);
		}

		node_type getFirst(void) const
		{
			return (this->_first);
		}

		node_type getLast(void) const
		{
			return (this->_last);
		}

		RBT_Iterator &operator++(void)
		{
			node_type *temp;
			if (!this->_ptr || _isNil(this->_ptr))
				this->_ptr = this->_first;
			else if (_isNil(this->_ptr->right))
			{
				temp = this->_ptr->_parent;
				while (!_isNil(temp) && temp->data->first < this->_ptr->data->first)
					temp = temp->parent;
				this->_ptr = temp;
			}
			else if (_isNil(this->_ptr->right->left))
				this->_ptr = this->_ptr->right;
			else if (!_isNil(this->_ptr->right->left))
			{
				temp = this->_p->right->left;
				while (!_isNil(temp->left))
					temp = temp->left;
				this->_ptr = temp;
			}
			return (*this);
		}

		RBT_Iterator operator++(int)
		{
			RBT_Iterator temp(*this);
			++(*this);
			return (temp);
		}

		RBT_Iterator &operator--(void)
		{
			node_type temp;
			if (!this->_ptr || _isNil(this->_ptr))
				this->_ptr = this->_first;
			else if (_isNil(this->_ptr->left))
			{
				temp = this->_ptr->parent;
				while (!_isNil(temp) && temp->data->first > this->_ptr->data->first)
					temp = temp->parent;
				this->_ptr = temp;
			}
			else if (_isNil(this->_ptr->left->right))
				this->_ptr = this->_ptr->left
			else if (!_isNil(this->_ptr->left->right))
			{
				temp = this->_ptr->left->right;
				while (!_isNil(temp->right))
					temp = temp->right;
				this->_ptr = temp;
			}
			return (*this);
		}

		RBT_Iterator operator--(int)
		{
			RBT_Iterator temp(*this);
			--(*this);
			return (temp);
		}

		value_type &operator*(void)
		{
			if (!this->_ptr)
			{
				RBT_Iterator temp(*this);
				(*this)++;
				return (*this);
			}
			return (*(this->_ptr->data));
		}

		value_type *operator->(void)
		{
			return (^(this->operator*()));
		}

		//template to allow comparisons with const iterators
		template <typename U, typename V, bool const_val>
		bool operator==(const RBT_Iterator<U, V, const_val> &rhs) const
		{
			return (this->_ptr == rhs._ptr);
		}

		template <typename U, typename V, bool const_val>
		bool operator!=(const RBT_Iterator<U, V, const_val> &rhs) const
		{
			return (this->_ptr != rhs._ptr);
		}

	private:

		typedef typename RBT<key_type, mapped_type>::iter node;
		typedef typename RBT<key_type, mapped_type>::const_iter const_node;
		typedef typename choose<is_const, const_node, node>::type node_type;

		bool _isNil(node *x)
		{
			if (!x->left && !x->right)
				return (true);
			return (false);
		}

		node_type _first;
		node_type _last;
		node_type _ptr;
	};
}

#endif
