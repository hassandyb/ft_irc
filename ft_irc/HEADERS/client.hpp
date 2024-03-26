/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 12:48:08 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "channel.hpp"
#include <vector>

class channel;

class client
{
	private :
		int Socket;
		std::string Username;
		std::string Nickname;
		std::vector<channel> Channels;
		
	public :
	

};