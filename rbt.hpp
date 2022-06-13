/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:52:17 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/13 15:20:14 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <iostream>
#include <memory>
#include "utils.hpp"
#include "rbt_iterator.hpp"

#define BLACK false
#define RED true

//TBD: add range constructor

namespace ft
{
	template <typename Key, typename T,
			class Alloc = std::allocator<pair<const Key, T> >, class Compare = std::less<Key> >
	class RBT
	{
	public:

		struct node;

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef node* iter;
		typedef const node* const_iter;
		typedef Compare key_compare;

		struct node
		{
			pointer data;
			node *parent;
			node *left;
			node *right;
			bool color;
		};

		RBT(void) : _size(0), _comp(), _alloc()
		{
			this->_nil = this->_node_alloc.allocate(1);
			this->_nil->color = BLACK;
			this->_nil->left = nullptr;
			this->_nil->right = nullptr;
			this->_root = this->_nil;
		}

		explicit RBT(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc)
		{
			this->_nil = this->_node_alloc.allocate(1);
			this->_nil->color = BLACK;
			this->_nil->left = nullptr;
			this->_nil->right = nullptr;
			this->_root = this->_nil;
		}

		~RBT(void) {}

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
			n->left = this->_nil;
			n->right = this->_nil;
			n->color = RED;

			node *y = nullptr;
			node *x = this->_root;
			while (x != this->_nil)
			{
				y = x;
				if (this->_comp(n->data->first, x->data->first))
					x = x->left;
				else if (this->_comp(x->data->first, n->data->first))
					x = x->right;
				else
				{
					return (x);
				}
			}
			n->parent = y;
			if (y == nullptr)
				this->_root = n;
			else if (this->_comp(n->data->first, y->data->first))
				y->left = n;
			else
				y->right = n;

			this->_size++;
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
			return (_findHelper(key, nullptr));
		}

		size_type erase(const key_type &k)
		{
			node *ptr = find(k);
			node *x;
			node *y;
			bool originalColor = ptr->color;

			if (ptr == this->_nil)
				return (0);
			if (ptr->left == this->_nil)
			{
				x = ptr->right;
				_nodeTransplant(ptr, x);
			}
			else if (ptr->right == this->_nil)
			{
				x = ptr->left;
				_nodeTransplant(ptr, x);
			}
			else
			{
				y = _min(ptr->right);
				originalColor = y->color;
				x = y->right;
				if (y->parent == ptr)
					x->parent = y;
				else
				{
					_nodeTransplant(y, x);
					y->right = ptr->right;
					y->right->parent = y;
				}
				_nodeTransplant(ptr, y);
				y->left = ptr->left;
				y->left->parent = y;
				y->color = ptr->color;
			}
			_clearNode(ptr);
			if (originalColor == BLACK)
				_fixErase(x);
			this->_size--;
			return (1);
		}

		void print(void) const
		{
			_printHelper("", this->_root, false);
		}

		allocator_type get_allocator(void) const
		{
			return (this->_alloc);
		}

		key_compare get_comp(void) const
		{
			return (this->_comp);
		}

		//for iterators
		iter begin(void) const
		{
			iter temp = this->_root;
			while (temp != this->_nil && temp->left != this->_nil)
				temp = temp->left;
			return (temp);
		}

		iter rbegin(void) const
		{
			iter temp = this->_root;
			while (temp != this->_nil && temp->right != this->_nil)
				temp = temp->_right;
			return (temp);
		}

		size_type max_size(void) const
		{
			return (this->_alloc.max_size());
		}

		iter getNil(void) const
		{
			return (this->_nil);
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
			if (y->left != this->_nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
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
			if (y->right != this->_nil)
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

		void _clearNode(node *n)
		{
			this->_alloc.deallocate(n->data, 1);
			this->_node_alloc.deallocate(n, 1);
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

		node *_findHelper(const key_type &key, node *ptr) const
		{
			node *n = this->_nil;

			if (this->_root == this->_nil)
				return (nullptr);
			if (ptr == nullptr)
				ptr = this->_root;
			if (ptr->data->first == key)
				return (ptr);
			if (!_hasChildren(ptr))
				return (this->_nil);
			if (this->_comp(key, ptr->data->first) && ptr->left == this->_nil)
				return (this->_nil);
			else if (this->_comp(key, ptr->data->first))
				n = _findHelper(key, ptr->left);
			if (this->_comp(ptr->data->first, key) && ptr->right == this->_nil)
				return (this->_nil);
			else if (this->_comp(ptr->data->first, key))
				n = _findHelper(key, ptr->right);
			return (n);

		}

		bool _hasChildren(node *n) const
		{
			if (n->left == nullptr && n->right == nullptr)
				return (false);
			return (true);
		}

		//replaces node x with node y
		void _nodeTransplant(node *x, node *y)
		{
			if (x->parent == nullptr)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->parent = x->parent;
		}

		//return pointer to node with smallest key (left-most in the tree)
		node *_min(node *ptr)
		{
			while (ptr->left != this->_nil)
				ptr = ptr->left;
			return (ptr);
		}

		void _fixErase(node *x)
		{
			node *y;
			while (x != this->_root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					y = x->parent->right;
					if (y->color == RED)
					{
						y->color = BLACK;
						x->parent->color = RED;
						_leftRotate(x->parent);
						y = x->parent->right;
					}
					if (y->left->color == BLACK && y->right->color == BLACK)
					{
						y->color = RED;
						x = x->parent;
					}
					else
					{
						if (y->right->color == BLACK)
						{
							y->left->color = BLACK;
							y->color = RED;
							_rightRotate(y);
							y = x->parent->right;
						}
						y->color = x->parent->color;
						x->parent->color = BLACK;
						y->right->color = BLACK;
						_leftRotate(x->parent);
						x = this->_root;
					}
				}
				else
				{
					y = x->parent->left;
					if (y->color == RED)
					{
						y->color = BLACK;
						x->parent->color = RED;
						_rightRotate(x->parent);
						y = x->parent->left;
					}
					if (y->right->color == BLACK && y->left->color == BLACK)
					{
						y->color = RED;
						x = x->parent;
					}
					else
					{
						if (y->left->color == BLACK)
						{
							y->right->color = BLACK;
							y->color = RED;
							_leftRotate(y);
							y = x->parent->left;
						}
						y->color = x->parent->color;
						x->parent->color = BLACK;
						y->left->color = BLACK;
						_rightRotate(x->parent);
						x = this->_root;
					}
				}
			}
			x->color = BLACK;
		}

		void _printHelper(const std::string& prefix, const node* n, bool isLeft) const
		{
			if (n != this->_nil && n != nullptr)
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node
				std::cout << n->data->first << std::endl;

				// enter the next tree level - left and right branch
				_printHelper(prefix + (isLeft ? "│   " : "    "), n->left, true);
				_printHelper(prefix + (isLeft ? "│   " : "    "), n->right, false);
			}
		}

		//pointer to root node of the tree
		node *_root;
		//pointer to sentinel nil node
		node *_nil;
		//size of the tree
		size_type _size;
		//comparison object
		key_compare _comp;
		//allocator object for values
		allocator_type _alloc;
		//allocator object for tree nodes
		std::allocator<node> _node_alloc;
	};
}

#endif
