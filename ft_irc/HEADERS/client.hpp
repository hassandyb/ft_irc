/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/27 18:14:43 by hed-dyb          ###   ########.fr       */
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
		std::vector<channel> Channels;

		bool registred;
		
	public :
		client();
		
		void setSocket(int Socket);
		void setNickname(std::string Nickname);
		void setUsername(std::string Username);
		
		int getSocket();
		std::string getNickname();
		std::string getUsername();
		
		

};