/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:13:32 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/25 22:38:40 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/server.hpp"


int main (int ac, char **av)
{
	if(ac != 3)
		std::cout << "Error : This program takes strictly it port and a password!" << std::endl;
	try
	{
		ft_build_server();
	}
	catch(const std::exception & e)
	{
	}
	
}




