/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:13:32 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/26 16:30:14 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HEADERS/server.hpp"


bool ft_valid_args(int & ac, char **av)
{
	
	if(ac != 3)
	{
		std::cout << "Usage :./ircserv <port> <password>" << std::endl;
		return false;
	}
	std::string port(av[1]);
	
	if(port.empty() == true || port.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Error : Invalid port!" << std::endl;
		return false;
	}
	std::istringstream iss_port(av[1]);
	int port_int;
	
	iss_port >> port_int;

	if(port_int < 1024 || port_int > 65535)
	{
		std::cout << "Error : The port should be between 1024 and 65535!" << std::endl;
		return false;
	}
	std::string password(av[2]);
	if(password.length() < 4 || password.length() > 24)
	{
		std::cout << "Error : Invalid password, we recommend a password between 4 and 24 characters." << std::endl;
		return false;
	}

	return true;
	
}


void server::ft_signal_handler(int signum)
{
	(void) signum;
	std::cout << "Signal received, closing the server..." << std::endl;
	exit(0);
}

int main (int ac, char **av)
{
	if(ft_valid_args(ac, av) == false)
		return 0;

	signal(SIGINT, server::ft_signal_handler);
	signal(SIGQUIT, server::ft_signal_handler);
	server s(av[1], av[2]);
	try
	{
		s.start();
		s.ft_close_all_socket();
	}
	
	catch(const std::exception & e)
	{
		std::cout << e.what() << std::endl;
		s.ft_close_all_socket();
	}
	
	return 0;
}
