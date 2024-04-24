/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/24 11:47:50 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "channel.hpp"
#include <iostream>
#include <vector>

class channel;

class client
{
	private :
		int Socket;
		std::string Nickname;
		std::string Username;
		
		// std::vector<channel> Channels;

		bool PassStage;// we make it true when the clinet enterd the correct password
		bool Regestred;//after the pass word is correct clinet must enter nick and user to pass this satge 
		
		std::string Realname;

		
		// remove later &&&&&&&&&&&&&&&&&&&&&&&&
		 int Fd; //-> client file descriptor
 		std::string IPadd; //-> client ip address
 
	public :
		client();
		
		//Setters : ----------------
		void setSocket(int Socket);
		void setNickname(std::string Nickname);
		void setUsername(std::string Username);
		void setPassStage(bool status);
		void setRegestred(bool status);
		void setRealname(std::string Realname);
		//Getters : ----------------
		int getSocket();
		std::string getNickname();
		std::string getUsername();
		bool getPassStage();
		bool getRegestred();
		std::string getRealname();

		// remove later &&&&&&&&&&&&&&&&&&&&&&&&
		int GetFd(){return Fd;} //-> getter for fd
 		void SetFd(int fd){Fd = fd;} //-> setter for fd
 		void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};