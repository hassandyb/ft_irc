/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:13:32 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/06 20:46:23 by hed-dyb          ###   ########.fr       */
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
	
	if(port.empty() == true || port.find_first_not_of("0123456789") != std::string::npos)//find_first_not_o return the index of the element thta does no exit in the sting passed as paramter..
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


// Signals : ----

bool server::ReceivedSignal = false;

void server::ft_signal_handler(int signum)
{
	(void) signum;
	// desplay a message message of clined deconcted one by one..
	// close clients sockets and pollfd soket  .. use a function ft_quit();
	server::ReceivedSignal = true;
}




int main (int ac, char **av)
{
	if(ft_valid_args(ac, av) == false)
		return 0;

	
	signal(SIGINT, server::ft_signal_handler);
	signal(SIGQUIT, server::ft_signal_handler);
	try
	{
		server s(av[1], av[2]);
		// a function that buildes a server ... 

		client c;// start modifing , just for testing ...
		while(server::ReceivedSignal == false)
		{
			// the poll function should be heree 
			std::string command;
			std::cout << "Command : ";
			getline(std::cin, command);




			s.ft_execute_command(command, c, 1);
			
		}
		
		// ft_close_sockets(); a fuction that closes sochets once a signal is recieved ...
	}
	
	catch(const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}




