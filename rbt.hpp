/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:52:17 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/12 01:52:17 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <iostream>
#include <memory>
#include "utils.hpp"

#define BLACK false
#define RED true

//TBD: do something about duplicate keys; make my life easier by suiting it more for containers

namespace ft
{
	template <typename Key, typename T, typename Alloc = std::allocator<pair<const Key, T> > >
	class RBT
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		struct node
		{
			pointer data;
			node *parent;
			node *left;
			node *right;
			bool color;
		};

		RBT(void) : _size(0), _root(nullptr) {}
		~RBT(void) {this->clear();}

		size_type size(void)
		{
			return (this->_size);
		}

		bool empty(void)
		{
			return (this->_size == 0);
		}

		//inserts element, fixes the tree and returns pointer to inserted element
		node *insert(const value_type &val)
		{
			node *n = this->_node_alloc.allocate(1);
			n->data = this->_alloc.allocate(1);
			this->_alloc.construct(n->data, val);
			n->parent = nullptr;
			n->left = nullptr;
			n->right = nullptr;
			n->color = RED;

			node *y = nullptr;
			node *x = this->_root;
			while (x != nullptr)
			{
				y = x;
				if (n->data->first < x->data->first)
					x = x->left;
				else
					x = x->right;
			}
			n->parent = y;
			if (y == nullptr)
				this->_root = n;
			else if (n->data->first < y->data->first)
				y->left = n;
			else
				y->right = n;

			//if n is the root node, recolor it to black and end
			if (n->parent == nullptr)
			{
				n->color = BLACK;
				return (n);
			}

			//if parent is root (grandparent is null) then end
			if (n->parent->parent == nullptr)
				return (n);

			//fix the tree
			_fixInsert(n);
			return (n);
		}

		//inserts element, fixes the tree and returns pointer to inserted element
		node *insert(const key_type &key, const mapped_type &val)
		{
			return (insert(make_pair(key, val)));
		}

		node *find(const key_type &key) const
		{
			_findHelper(key, nullptr);
		}

	private:

		RBT(const RBT &copy) {*this = copy;}

		const RBT &operator=(const RBT &copy)
		{
			this->_size = copy._size;
			this->_root = copy._root;
			return (*this);
		}

		//performs left-rotation on node x
		void _leftRotate(node *x)
		{
			node *y = x->right;
			x->right = y->left;
			if (y->left != nullptr)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->keft = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		//performs righ-rotation on node x
		void _rightRotate(node *x)
		{
			node *y = x->left;
			x->left = y->right;
			if (y->right != nullptr)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				this->_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void _fixInsert(node *x)
		{
			node *y;
			while (x->parent->color == RED)
			{
				if (x->parent == x->parent->parent->right)
				{
					y = x->parent->parent->left; //uncle of x
					if (y->color == RED)
					{
						y->color = BLACK;
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					}
					else
					{
						if (x == x->parent->left)
						{
							x = x->parent;
							_rightRotate(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						_leftRotate(x->parent->parent);
					}
				}
				else
				{
					y = x->parent->parent->right; //uncle of x
					if (y->color == RED)
					{
						y->color = BLACK;
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					}
					else
					{
						if (x == x->parent->right)
						{
							x = x->parent;
							_leftRotate(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						_rightRotate(x->parent->parent);
					}
				}
				if (x == this->_root)
					break ;
			}
			this->_root->color = BLACK;
		}

		node *_findHelper(const key_type &key, node *ptr)
		{
			node *n = nullptr;

			if (this->_root == nullptr)
				return (nullptr);
			if (ptr == nullptr)
				ptr = this->_root;
			if (ptr->data->first == key)
				return (ptr);
			if (!_hasChildren(ptr))
				return (nullptr);
			if (ptr->data->first > key && ptr->left == nullptr)
				return (nullptr);
			else if (ptr->data->first > key)
				n = _findHelper(key, ptr->left);
			if (ptr->data->first < key && ptr->right == nullptr)
				return (nullptr);
			else if (ptr->data->first < key)
				n = _findHelper(key, ptr->right);
			return (n);

		}

		bool _hasChildrem(node *n)
		{
			if (n->left == nullptr && n->right == nullptr)
				return (false);
			return (true);
		}

		//pointer to root node of the tree
		node *_root;
		//size of the tree
		size_type _size;
		//allocator object for values
		allocator_type _alloc;
		//allocator object for tree nodes
		std::allocator<node> _node_alloc;
	};
}

#endif
