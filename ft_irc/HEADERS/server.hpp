/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 15:27:59 by hed-dyb          ###   ########.fr       */
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
#include <ctime>
#include <poll.h>
#include <netinet/in.h>
#include <unistd.h>



class server
{
	private :
		int socketFd;
		int Port;
		std::string Password;

		struct sockaddr_in  address;
		std::vector<client> Clients;
		std::vector<channel> Channels;
 		
 		std::vector<struct pollfd> fds;
		
	public :
		//parametrized constructor ...
		server(char * port, char * Password);
		


		// methods
		void start();
		std::string read_from_client(int Socket);

		// execute command
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
		static void ft_signal_handler(int signum);


		// Commands : ---------------------
		bool ft_is_registred(client & Client, int Socket);
		void ft_pass(std::vector<std::string> & Cmds, client & Client, int Socket);
		void ft_user(std::vector<std::string> & Cmds, client & Client, int Socket);
		void ft_nick(std::vector<std::string> & Cmds, client & Client, int Socket);
		bool ft_nick_already_used(std::string nick);
		void ft_inform_clients(std::string msg);
		void ft_try_to_join(std::string channel_name, std::string password, client & Client);
		void ft_join(std::vector<std::string> Cmds, client & Client, int Socket);
		bool ft_channel_exist(std::string channel_name);
		void ft_join_message(std::string & channel_name, client & Client, channel & new_channel);
		void ft_inform_the_rest(channel & Channel, client & Client);
		void ft_invite(std::vector<std::string> Cmds, client & Client, int Socket);
		void ft_privmsg(std::vector<std::string> Cmds, client & Client, int Socket);
		void ft_priv_msg_client(std::string Recipient_name, client & Client, std::string message);
		void ft_priv_msg_channel(std::string Recipient_channel, client & Client, std::string message);
		void ft_mode(std::vector<std::string>  Cmds, client & Client, int Socket);
		void ft_mode_invite(channel & Channel, client & Client, bool sign);
		void ft_mode_topic(channel & Channel, client & Client, bool sign);
		void ft_mode_password(channel & Channel, client & Client, bool sign, std::string arg);
		void ft_mode_limit(channel & Channel, client & Client, bool sign, std::string max);
		void ft_mode_operator(channel & Channel, client & Client, bool sign, std::string target_client);
		std::string getJoke();




		void ft_part(std::vector<std::string> Cmds, client & Client, int Socket);
		void ft_leave_channel(channel & Channel,client &  Client, std::vector<std::string> & Cmds);
		void ft_kick(std::vector<std::string> Cmds, client & Client, int Socket);
		void ft_kick_users(channel & Channel, client & Client, std::vector<std::string> Cmds);
		void ft_quit(std::vector<std::string> Cmds, client & Client, int Socket);
		void ft_topic(std::vector<std::string> Cmds, client & Client, int Socket);
		// utilts -----------------
		


		bool ft_send(int socket, const void * buff, size_t len, int flags);
		bool ft_find_a_client(std::string Nick);
		
		bool ft_find_a_channel(std::string Channel_name);
		channel & ft_get_a_channel(std::string Channel_name);
		client & ft_get_client(std::string nick);
		void ft_send_msg_to_all(std::vector<client> container, std::string msg);
		void ft_delete_client(int sock);
		void ft_delete_client(client Client);
		void ft_delete_channel(std::string Channel_name);
		void ft_close_all_socket();
		
};	


std::vector<std::string> ft_split_with_comma(std::string list);
void ft_split_with_spaces(std::vector<std::string> & Cmds, std::string Command);
size_t ft_string_to_size_t(std::string str);



