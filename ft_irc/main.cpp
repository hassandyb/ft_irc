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


// __________________

//	mode #group +p/u/l htjb



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
		s.SerSocket();

		// client c;// start modifing , just for testing ...
		while(server::ReceivedSignal == false)
		{
			// std::cout << "kkk ..." << std::endl;
			if((poll(s.getFds().data(), s.getFds().size(), -1) == -1) && server::ReceivedSignal == false)
				throw(std::runtime_error("poll() faild"));
			// std::cout << "here ..." << std::endl;
			for(size_t i = 0; i < s.getFds().size(); i++)
			{
				// for the server socket i = 0 (fd = 3) , to accept and create new clients only no reading no writing
				if (i == 0 && s.getFds()[i].revents & POLLIN)
				{
					s.AcceptNewClient();
					continue; // skip bcoz no reading or wriding should be done here
				}
				if (s.getFds()[i].revents & POLLIN)
					s.ReceiveNewData(s.getFds()[i].fd);
				if (s.getFds()[i].revents & POLLHUP)
				{
					std::cout <<"disconnected" << std::endl;
					s.ClearClients(s.getFds()[i].fd);  // deled from the clients
					i--;
				}
			}
		}
		
		s.CloseFds();
	}
	
	catch(const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}




