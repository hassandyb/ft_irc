/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/31 17:06:39 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "client.hpp"
#include "channel.hpp"

#include <unistd.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <sys/socket.h>
#include <string>
#include <cctype>




class server
{
	private :
		int Socket;
		int Port;
		std::string Password;

		
		std::vector<client> Clients;
		std::vector<channel> Channels;
	public :
		//parametrized constructor ...
		server(char * port, char * Password);
		

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


		// Commands : ---------------------
		bool ft_is_registred(client & Client, int Socket);
		void ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket);
		void ft_user(std::vector<std::string> & Cmds, client & Client, int Socket);
		void ft_nick(std::vector<std::string> & Cmds, client & Client, int Socket);
		bool ft_nick_already_used(std::string nick);
		void ft_inform_clients(std::string msg);
		void ft_join_channel(std::vector<std::string> & Cmds, size_t i,  client & Client, bool password);
		void ft_join(std::vector<std::string> Cmds, client & Client, int Socket);
		bool ft_channel_exist(std::string channel_name);
		bool ft_send(int socket, const void * buff, size_t len, int flags);
		channel & ft_find_channel(std::string channel_name);


		
};	




