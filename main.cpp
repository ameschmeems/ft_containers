/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:53:32 by kpucylo           #+#    #+#             */
/*   Updated: 2022/05/31 14:43:36 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_access_iterator.hpp"
#include <iostream>
#include <vector>

class A {public: int i; A():i(5){} };

int main(void)
{
	std::vector<A> vector(2);
	vector.push_back(A());
	std::vector<A>::iterator it = vector.begin();
	std::cout << it->i << std::endl;
}
