/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/15 19:35:52 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//for std version
#ifdef STD
# include <map>
# include <vector>
# include <stack>
namespace ft = std;
#endif
//for ft version
#ifndef STD
// # include "map.hpp"
# include "vector.hpp"
# include "stack.hpp"
#endif

#include "rbt.hpp"
#include "rbt_iterator.hpp"

#include <map>

int main(void)
{
	// ft::RBT<int, int> tree;
	// ft::RBT_Iterator<ft::RBT<int, int>::node, ft::RBT<int, int> > it(tree.getNil());
	// ft::const_RBT_Iterator<ft::RBT<int, int>::node, ft::RBT<int, int> > it2 = it;
	// it2 = it;
	// tree.insert(1, 1);
	// tree.insert(2, 2);
	// tree.insert(3, 3);
	// tree.insert(4, 4);
	// tree.insert(5, 5);
	// tree.insert(6, 6);
	// tree.insert(7, 7);
	// tree.insert(8, 8);
	// tree.insert(9, 9);
	// tree.insert(10, 10);
	// tree.insert(11, 11);
	// tree.insert(12, 12);
	// tree.insert(13, 13);
	// tree.insert(14, 14);
	// tree.insert(15, 15);
	// tree.insert(16, 15);
	// tree.insert(17, 15);
	// tree.insert(18, 15);
	// tree.insert(19, 15);
	// tree.print();
	// it = tree.begin();
	// it2 = it;
	// std::cout << (it == it2) << std::endl;
	// std::cout << (it != it2) << std::endl;
	// it2++;
	// std::cout << (it == it2) << std::endl;
	// std::cout << (it != it2) << std::endl;
	// std::cout << "uno momento de bruh" << std::endl;
	// for (int i = 0; i < 19; i++)
	// {
	// 	// it->second = 5;
	// 	it++;
	// }
	// it2 = tree.begin();
	// for (int i = 0; i < 19; i++, it2++)
	// 	std::cout << it2->second << std::endl;
	// // std::cout << it->first << std::endl;
	// for (int i = 0; i < 19; i++, --it)
	// 	std::cout << it->first << std::endl;
	std::map<int, int> mp;
	mp.insert(std::make_pair(1, 1));
	mp.insert(std::make_pair(2, 1));
	mp.insert(std::make_pair(3, 1));
	mp.insert(std::make_pair(4, 1));
	mp.insert(std::make_pair(5, 1));
	mp.insert(std::make_pair(6, 1));
	mp.insert(std::make_pair(7, 1));
	std::map<int, int>::iterator it = mp.begin();
	for (; it != mp.end(); it++)
		std::cout << it->second << std::endl;
	it = mp.begin();
	it->second = 15;
	it = mp.begin();
	for (; it != mp.end(); it++)
		std::cout << it->second << std::endl;
}
