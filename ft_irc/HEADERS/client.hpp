/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 14:52:25 by hed-dyb          ###   ########.fr       */
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
		bool Quit;
		
		std::string message; // the message that the client will send to the server adding it to the client class so we can handle the CTL+D signal

 
	public :
		client();
		client(client const & other);
		client & operator=(client const & other);// update later
		~client();


		void clearMessage();

		
		//Setters : ----------------
		void setMessage(std::string message);
		void setSocket(int Socket);
		void setNickname(std::string Nickname);
		void setUsername(std::string Username);
		void setPassStage(bool status);
		void setRegestred(bool status);
		void setRealname(std::string Realname);
		void setQuit(bool Quit);
		//Getters : ----------------
		std::string getMessage();
		int getSocket();
		std::string getNickname();
		std::string getUsername();
		bool getPassStage();
		bool getRegestred();
		std::string getRealname();
		bool getQuit();


		
};