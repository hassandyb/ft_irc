/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 15:27:05 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "client.hpp"
#include "channel.hpp"


#include <exception>
#include <iostream>
#include <sstream>
#include <signal.h>


class server
{
	private :
		int Socket;
		int Port;
		std::string Password;

		
		std::vector<client> Clients;
		std::vector<channel> Channels;
	public :
		
		void ft_execute_command(std::string Command, client & Client, int Socket);
		
		// Setters ---------------------
		void setSocket(int Socket);
		void setPort(int Port);
		void setPassword(std::string Password);

		// Getters ---------------------
		int getSocket();
		int getPort();
		std::string getPassword();
		
		
		
		//Signals : ---------------------
		static bool ReceivedSignal;
		static void ft_signal_handler(int signum);
};