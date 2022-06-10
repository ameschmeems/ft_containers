/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:19:26 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/10 15:26:24 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
	public:

		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		//construct stack with copy of container
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

		~stack(void) {}

		//checks whether the stack is empty
		bool empty(void) const
		{
			return (this->c.empty());
		}

		//returns containers size
		size_type size(void) const
		{
			return (this->c.size());
		}

		//returns reference to the first element of stack
		value_type &top(void)
		{
			return (this->c.back());
		}

		const value_type &top(void) const
		{
			return (this->c.back());
		}

		//push element to top of the stack
		void push(const value_type &val)
		{
			this->c.push_back(val);
		}

		//remove top element of stack
		void pop(void)
		{
			this->c.pop_back();
		}

		//non-member friend declarations
		template<class _T, class _Container>
		friend bool operator==(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

		template<class _T, class _Container>
		friend bool operator!=(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

		template<class _T, class _Container>
		friend bool operator<(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

		template<class _T, class _Container>
		friend bool operator<=(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

		template<class _T, class _Container>
		friend bool operator>(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

		template<class _T, class _Container>
		friend bool operator>=(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

	protected:

		container_type c;
	};

	//non-member overloads

	template<class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
