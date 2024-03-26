/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:43 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 13:00:53 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"
#include <vector>

class client;

class channel
{
	private :
		std::string Name;
		std::string Topic;
		std::string Password;
		size_t		Max;

		
		std::vector<client > Members;
		std::vector<client > operators;
		std::vector<client > invited;
		
		bool InvitaionStatus;
		bool TopicStatus;
		bool PassWordStatus;
		bool AdminStatus;
	
	public :
		
		



		
};