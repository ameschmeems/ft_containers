/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:22:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/16 16:17:31 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	template <typename T, class Tree>
	class const_RBT_Iterator;

	template <typename T, class Tree>
	class RBT_Iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:

		typedef typename Tree::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		RBT_Iterator(T *nil = nullptr) : _ptr(), _nil(nil) {}

		RBT_Iterator(T *ptr,T *nil) : _ptr(ptr), _nil(nil) {}

		RBT_Iterator(const RBT_Iterator &copy)
			: _ptr(copy._ptr), _nil(copy._nil) {}
		
		virtual ~RBT_Iterator(void) {}

		RBT_Iterator &operator=(const RBT_Iterator &copy)
		{
			this->_ptr = copy._ptr;
			this->_nil = copy._nil;
			this->_prev = copy._prev;
			return (*this);
		}

		T *base(void) const
		{
			return (this->_ptr);
		}

		reference operator*(void) const
		{
			return (*(this->_ptr->data));
		}

		pointer operator->(void) const
		{
			return (&(this->operator*()));
		}

		//not sure what to do when iterator reaches the end

		RBT_Iterator &operator++(void)
		{
			T *temp = this->_ptr;
			if (temp == nullptr)
				temp = this->_prev;
			else if (temp->right != this->_nil)
			{
				temp = temp->right;
				while (temp->left != this->_nil)
					temp = temp->left;
			}
			else if (temp->parent && temp == temp->parent->left)
				temp = temp->parent;
			else if (temp->parent && temp == temp->parent->right)
			{
				while (temp->parent && temp == temp->parent->right)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else
					temp = this->_nil;
			}
			this->_prev = this->_ptr;
			this->_ptr = temp;
			return (*this);
		}

		RBT_Iterator operator++(int)
		{
			RBT_Iterator temp = *this;
			++(*this);
			return (temp);
		}

		RBT_Iterator &operator--(void)
		{
			T *temp = this->_ptr;
			if (!temp->parent && temp->left == this->_nil)
				temp = temp->parent;
			else if (temp == this->_nil)
				temp = this->_nil->parent;
			else if (temp->left != this->_nil && temp->left)
			{
				temp = temp->left;
				while (temp->right != this->_nil)
				{
					temp = temp->right;
				}
			}
			else if (temp->parent && temp == temp->parent->right)
				temp = temp->parent;
			else if (temp->parent && temp == temp->parent->left)
			{
				while (temp->parent && temp == temp->parent->left)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else 
					temp = nullptr;
			}
			else
				temp = this->_nil->parent;
			this->_prev = this->_ptr;
			this->_ptr = temp;
			return (*this);
		}

		RBT_Iterator operator--(int)
		{
			RBT_Iterator temp = *this;
			--(*this);
			return (temp);
		}

		T *getNil(void) const
		{
			return (this->_nil);
		}

		T *getPrev(void) const
		{
			return (this->_prev);
		}

		bool operator==(const const_RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() == rhs.base());
		}

		bool operator==(const RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() == rhs.base());
		}

		bool operator!=(const const_RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() != rhs.base());
		}

		bool operator!=(const RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() != rhs.base());
		}

	private:

		T *_ptr;
		T *_nil;
		T *_prev;
	};

	template <typename T, class Tree>
	class const_RBT_Iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:

		typedef const typename Tree::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		const_RBT_Iterator(T *nil = nullptr) : _ptr(), _nil(nil) {}

		const_RBT_Iterator(T *ptr,T *nil) : _ptr(ptr), _nil(nil) {}

		const_RBT_Iterator(const const_RBT_Iterator &copy)
			: _ptr(copy._ptr), _nil(copy._nil) {}

		const_RBT_Iterator(const RBT_Iterator<T, Tree> &copy)
		{
			*this = copy;
		}
		
		virtual ~const_RBT_Iterator(void) {}

		const_RBT_Iterator &operator=(const const_RBT_Iterator &copy)
		{
			this->_ptr = copy._ptr;
			this->_nil = copy._nil;
			this->_prev = copy._prev;
			return (*this);
		}

		const_RBT_Iterator &operator=(const RBT_Iterator<T, Tree> &copy)
		{
			this->_ptr = copy.base();
			this->_nil = copy.getNil();
			this->_prev = copy.getPrev();
			return (*this);
		}

		T *base(void) const
		{
			return (this->_ptr);
		}

		const reference operator*(void) const
		{
			return (*(this->_ptr->data));
		}

		const pointer operator->(void) const
		{
			return (&(this->operator*()));
		}

		//not sure what to do when iterator reaches the end

		const_RBT_Iterator &operator++(void)
		{
			T *temp = this->_ptr;
			if (temp == nullptr)
				temp = this->_prev;
			else if (temp->right != this->_nil)
			{
				temp = temp->right;
				while (temp->left != this->_nil)
					temp = temp->left;
			}
			else if (temp->parent && temp == temp->parent->left)
				temp = temp->parent;
			else if (temp->parent && temp == temp->parent->right)
			{
				while (temp->parent && temp == temp->parent->right)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else 
					temp = this->_nil;
			}
			this->_prev = this->_ptr;
			this->_ptr = temp;
			return (*this);
		}

		const_RBT_Iterator operator++(int)
		{
			const_RBT_Iterator temp = *this;
			++(*this);
			return (temp);
		}

		const_RBT_Iterator &operator--(void)
		{
			T *temp = this->_ptr;
			if (temp == this->_nil)
				temp = this->_nil->parent;
			else if (temp->left != this->_nil)
			{
				temp = temp->left;
				while (temp->right != this->_nil)
					temp = temp->right;
			}
			else if (temp->parent && temp == temp->parent->right)
				temp = temp->parent;
			else if (temp->parent && temp == temp->parent->left)
			{
				while (temp->parent && temp == temp->parent->left)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else
					temp = nullptr;
			}
			this->_prev = this->_ptr;
			this->_ptr = temp;
			return (*this);
		}

		const_RBT_Iterator operator--(int)
		{
			const_RBT_Iterator temp = *this;
			--(*this);
			return (temp);
		}

		bool operator==(const const_RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() == rhs.base());
		}

		bool operator==(const RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() == rhs.base());
		}

		bool operator!=(const const_RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() != rhs.base());
		}

		bool operator!=(const RBT_Iterator<T, Tree> &rhs) const
		{
			return (this->base() != rhs.base());
		}

	private:

		T *_ptr;
		T *_nil;
		T *_prev;
	};
}

#endif
