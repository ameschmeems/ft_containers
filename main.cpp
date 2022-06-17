/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/17 20:09:25 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//for std version
#ifdef STD
# include <map>
# include <vector>
# include <stack>
namespace ft = std;
#else
# include "map.hpp"
# include "vector.hpp"
# include "stack.hpp"
#endif

#include <iostream>

int main(void)
{
	{
		std::cout << "#######################################################" << std::endl;
		std::cout << "#------------------------ MAP ------------------------#" << std::endl;
	#ifdef STD
		std::cout << "#------------------------ STL ------------------------#" << std::endl;
	#else
		std::cout << "#------------------------ FT  -----------------------#" << std::endl;
	#endif
		std::cout << "#######################################################" << std::endl << std::endl;
		ft::map<int, std::string> mp;

		mp[0] = "I";
		mp[1] = "like";
		mp[2] = "frogs";
		mp[3] = ".";

		std::cout << "Insertion and printing using operator[]" << std::endl;
		std::cout << " - " << mp[0] << std::endl;
		std::cout << " - " << mp[1] << std::endl;
		std::cout << " - " << mp[2] << std::endl;
		std::cout << " - " << mp[3] << std::endl;

		std::cout << "Printing using iterators (from begin to end)" << std::endl;
		ft::map<int, std::string>::iterator it = mp.begin();
		for (; it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;

		std::cout << "Printing using iterators (from end to begin)" << std::endl;
		it = --(mp.end());
		for (; it != mp.begin(); it--)
			std::cout << " - " << it->second << std::endl;
		std::cout << " - " << it->second << std::endl;

		std::cout << "Printing from a new map after copying" << std::endl;
		ft::map<int, std::string> mp2 = mp;
		it = mp2.begin();
		for (; it != mp2.end(); it++)
			std::cout << " - " << it->second << std::endl;
		
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.erase(3);
		std::cout << "After removing the last element using key" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.erase(mp.begin());
		std::cout << "After removing first element using iterator" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.erase(mp.begin(), mp.end());
		std::cout << "After removing all remaining elements" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.insert(mp2.begin(), mp2.end());
		std::cout << "After inserting range from copied Map" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.insert(ft::make_pair(8, "borgor"));
		std::cout << "After inserting with key 8" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.insert(ft::make_pair(6, "duck"));
		std::cout << "After inserting with key 6" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		it = mp.find(6);
		std::cout << "Using 'find' to get element with key 6" << std::endl;
		std::cout << " - " << it->second << std::endl;
		it = mp.find(2);
		std::cout << "Using 'find' to get element with key 2" << std::endl;
		std::cout << " - " << it->second << std::endl;
		it = mp.lower_bound(3);
		std::cout << "Lower bound of key 3" << std::endl;
		std::cout << " - " << it->second << std::endl;
		it = mp.upper_bound(3);
		std::cout << "Upper bound of key 3" << std::endl;
		std::cout << " - " << it->second << std::endl;
		std::cout << "Traversing with reverse iterator" << std::endl;
		ft::map<int, std::string>::reverse_iterator rit = mp.rbegin();
		for (; rit != mp.rend(); rit++)
			std::cout << " - " << rit->second << std::endl;
		std::cout << "Removing element with key 3, and then checking if previously\ncreated iterator begin() is still valid" << std::endl;
		it = mp.begin();
		mp.erase(3);
		for (; it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		it = mp.begin();
		std::cout << "comparing iterator to begin (should be the same)" << std::endl;
		std::cout << " - it == begin: " << (it == mp.begin()) << std::endl;
		std::cout << " - it == begin: " << (it != mp.begin()) << std::endl;
		it++;
		std::cout << "comparing iterator to begin (should be different)" << std::endl;
		std::cout << " - it == begin: " << (it == mp.begin()) << std::endl;
		std::cout << " - it == begin: " << (it != mp.begin()) << std::endl;
		std::cout << "Checking behavior of ft::make_pair" << std::endl;
		ft::pair<std::string, std::string> p = ft::make_pair("forg", "phroge");
		std::cout << " - First: " << p.first << std::endl;
		std::cout << " - Second: " << p.second << std::endl;
		std:: cout << "Trying to add element with existing key (6)" << std::endl;
		mp.insert(ft::make_pair(6, "handborgor"));
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		ft::map<int, std::string> new_mp;
		new_mp.insert(ft::make_pair(1, "I"));
		new_mp.insert(ft::make_pair(2, "enjoy"));
		new_mp.insert(ft::make_pair(3, "containers"));
		new_mp.insert(ft::make_pair(4, "(not really)"));
		std::cout << "Newly created map" << std::endl;
		for (it = new_mp.begin(); it != new_mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Swapping maps and making sure that previously declared iterators are valid" << std::endl;
		it = new_mp.begin();
		ft::map<int, std::string>::iterator it2 = mp.begin();
		mp.swap(new_mp);
		std::cout << " - old mp.begin == curent new_mp.begin: " << (it2 == new_mp.begin()) << std::endl;
		std::cout << " - old new_mp.begin == curent mp.begin: " << (it == mp.begin()) << std::endl;
		std::cout << "Max_size function (calls max_size of\ncontainers std::allocator)" << std::endl;
		std::cout << " - " << mp.max_size() << std::endl << std::endl;
	}
	{
		std::cout << "#######################################################" << std::endl;
		std::cout << "#----------------------- VECTOR ----------------------#" << std::endl;
	#ifdef STD
		std::cout << "#------------------------ STL ------------------------#" << std::endl;
	#else
		std::cout << "#------------------------ FT  ------------------------#" << std::endl;
	#endif
		std::cout << "#######################################################" << std::endl << std::endl;
		ft::vector<std::string> vec;
		vec.push_back("frog");
		vec.push_back("toad");
		vec.push_back("hamburger");
		vec.push_back("caffeine");
		vec.push_back("pizza");
		std::cout << "Creating vector, pushing some elements and\niterating with iterator" << std::endl;
		ft::vector<std::string>::iterator it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Iterating again but this time with const iterator" << std::endl;
		ft::vector<std::string>::const_iterator cit = vec.begin();
		for (; cit != vec.end(); cit++)
			std::cout << " - " << *cit << std::endl;
		std::cout << "Comparing the two iterators (should be the same)" << std::endl;
		std::cout << " - it == cit: " << (it == cit) << std::endl;
		std::cout << " - it > cit: " << (it > cit) << std::endl;
		std::cout << " - it < cit: " << (it < cit) << std::endl;
		std::cout << " - it >= cit: " << (it >= cit) << std::endl;
		std::cout << " - it <= cit: " << (it <= cit) << std::endl;
		it = vec.begin();
		std::cout << "Comparing the two iterators (should be different)" << std::endl;
		std::cout << " - it == cit: " << (it == cit) << std::endl;
		std::cout << " - it > cit: " << (it > cit) << std::endl;
		std::cout << " - it < cit: " << (it < cit) << std::endl;
		std::cout << " - it >= cit: " << (it >= cit) << std::endl;
		std::cout << " - it <= cit: " << (it <= cit) << std::endl;
		std::cout << "Printing third element using begin + 2" << std::endl;
		std::cout << " - " << *(it + 2) << std::endl;
		std::cout << "Printing third element using operator[]" << std::endl;
		std::cout << " - " << it[2] << std::endl;
		std::cout << "Iterating with reverse_iterators" << std::endl;
		ft::vector<std::string>::reverse_iterator rit = vec.rbegin();
		for (; rit != vec.rend(); rit++)
			std::cout << " - " << *rit << std::endl;
		std::cout << "Comparing reverse iterator with const_reverse_iterator\n(should be different)" << std::endl;
		ft::vector<std::string>::const_reverse_iterator crit = vec.rbegin();
		std::cout << " - crit == rit: " << (crit == rit) << std::endl;
		std::cout << " - crit != rit: " << (crit != rit) << std::endl;
		std::cout << " - crit >= rit: " << (crit >= rit) << std::endl;
		std::cout << " - crit <= rit: " << (crit <= rit) << std::endl;
		std::cout << " - crit > rit: " << (crit > rit) << std::endl;
		std::cout << " - crit < rit: " << (crit < rit) << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "Vector after pushing 3 new objects" << std::endl;
		vec.push_back("duck");
		vec.push_back("capybara");
		vec.push_back("lizard");
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "After pushing another object" << std::endl;
		vec.push_back("bruh");
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "After popping the last object" << std::endl;
		vec.pop_back();
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "After resizing to 8" << std::endl;
		vec.resize(8);
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "After resizing to 32" << std::endl;
		vec.resize(32);
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		ft::vector<std::string> v(8, "42");
		vec.assign(v.begin(), v.end());
		std::cout << "Vector after using assign to change contents" << std::endl;
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "After resizing to 4" << std::endl;
		vec.resize(4);
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "Changing first and last element of vector using operator[]" << std::endl;
		vec[0] = "frorg";
		vec[3] = "dogue";
		it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << " - " << *it << std::endl;
		std::cout << "Vector size" << std::endl;
		std::cout << " - " << vec.size() << std::endl;
		std::cout << "Vector capacity" << std::endl;
		std::cout << " - " << vec.capacity() << std::endl;
		std::cout << "Vector max_size" << std::endl;
		std::cout << " - " << vec.max_size() << std::endl;
		std::cout << "Return value of front()" << std::endl;
		std::cout << " - " << vec.front() << std::endl;
		std::cout << "Return value of back()" << std::endl;
		std::cout << " - " << vec.back() << std::endl;
		std::cout << "Capacity after using reserve(42)" << std::endl;
		vec.reserve(42);
		std::cout << " - " << vec.capacity() << std::endl;
		ft::vector<std::string> ve = vec;
		ve[0] = "toad";
		ve[2] = "borgor";
		std::cout << "New vector" << std::endl;
		it = ve.begin();
		for (; it != ve.end(); it++)
			std::cout << " - " << *it << std::endl;
		it = vec.begin();
		vec.swap(ve);
		std::cout << "New vector after swapping with old vector\niterated with old iterator to make sure its valid" << std::endl;
		for (; it != ve.end(); it++)
			std::cout << " - " << *it << std::endl;
	}
}
