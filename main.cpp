/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/16 18:05:47 by kpucylo          ###   ########.fr       */
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
		std::cout << "#-------------------------STL-------------------------#" << std::endl;
	#else
		std::cout << "#--------------------------FT-------------------------#" << std::endl;
	#endif
		std::cout << "#######################################################" << std::endl;
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
		std::cout << "After removing the last element" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		mp.erase(mp.begin());
		std::cout << "After removing first element" << std::endl;
		for (it = mp.begin(); it != mp.end(); it++)
			std::cout << " - " << it->second << std::endl;
		std::cout << "Map size" << std::endl;
		std::cout << " - " << mp.size() << std::endl;
		std::cout << "Is Map empty" << std::endl;
		std::cout << " - " << mp.empty() << std::endl;
		// mp.clear();
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
		std::cout << it->second << std::endl;
		it = mp.upper_bound(3);
		std::cout << "Upper bound of key 3" << std::endl;
		std::cout << it->second << std::endl;
	}
}
