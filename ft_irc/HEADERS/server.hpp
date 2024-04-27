/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 11:28:45 by hed-dyb          ###   ########.fr       */
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


//remove later &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
//-------------------------------------------------------//
#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color




class server
{
	private :
		int Socket;
		int Port;
		std::string Password;

		
		std::vector<client> Clients;
		std::vector<channel> Channels;

		// remove later &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

		
 		int SerSocketFd; //-> server socket file descriptor
 		static bool Signal; //-> static boolean for signal
 		
 		std::vector<struct pollfd> fds; //-> vector of pollfd
		
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

		// remove later &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		void SerSocket();//-> server socket creation
		 std::vector<struct pollfd>& getFds()  {return fds;}
		
 		void ServerInit(); //-> server initialization
 		
 		void AcceptNewClient(); //-> accept new client
 		void ReceiveNewData(int fd); //-> receive new data from a registered client
 		
 		void CloseFds(); //-> close file descriptors
 		void ClearClients(int fd); //-> clear clients
		client & ft_get_client_fd(int fd);

		// int Socket;
		// int Port;
		// std::string Password;
		// std::vector<client> Clients;
		// std::vector<channel> Channels;

		
		void ft_print_data()
		{
			std::cout << ":server data : --------------" << std::endl;
			std::cout << "Clients : ";
			for(size_t i = 0; i < Clients.size(); i++)
			{
				std::cout << Clients[i].getNickname() << " ";
			}
			std::cout << std::endl;
			for(size_t i = 0; i < Channels.size() ; i++)
			{
				std::cout << "Channel " << Channels[i].getName() << "  ";
				std::cout << "M : ";
				std::vector<client> Members = Channels[i].getMembers();
				for(size_t i = 0; i < Members.size(); i++)
				{
					std::cout << Members[i].getNickname() << " ";
				}
				std::cout << "A : ";
				std::vector<client> Admins = Channels[i].getAdmins();
				for(size_t i = 0; i < Admins.size(); i++)
				{
					std::cout << Admins[i].getNickname() << " ";
				}
				std::cout << "I : ";
				std::vector<client> Invited = Channels[i].getInvited();
				for(size_t i = 0; i < Invited.size(); i++)
				{
					std::cout << Invited[i].getNickname() << " ";
				}
	
				std::cout << "\n  Status : "<< "p" << Channels[i].getPassWordStatus() << "i" << Channels[i].getInvitaionStatus() << "t" << Channels[i].getTopicStatus() << "l" << Channels[i].getAdminStatus() << std::endl;
				std::cout << " ---- " << std::endl;
			}
		}
		
};	


std::vector<std::string> ft_split_with_comma(std::string list);
void ft_split_with_spaces(std::vector<std::string> & Cmds, std::string Command);
size_t ft_string_to_size_t(std::string str);



