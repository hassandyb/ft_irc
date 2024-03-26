/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:38 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 14:09:26 by hed-dyb          ###   ########.fr       */
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
		// int Socket;
		// int Port;
		// std::string Password;

		
		// std::vector<client> Clients;
		// std::vector<channel> Channels;
	public :
		
		
		//Signals : ---------------------
		static bool ReceivedSignal;
		static void ft_signal_handler(int signum);
};