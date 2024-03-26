/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:43 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 15:19:07 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"
#include <iostream>
#include <vector>

class client;

class channel
{
	private :
		std::string Name;
		std::string Topic;
		std::string Password;
		size_t		Max;


		bool InvitaionStatus;
		bool TopicStatus;
		bool PassWordStatus;
		bool AdminStatus;

		std::vector<client > Members;
		std::vector<client > Admins;
		std::vector<client > Invited;
			
	public :
		void ft_channel_init();
		
		// Getters / Setters ------------------
		void setName(std::string Name);
		void setTopic(std::string Topic);
		void setPassword(std::string Password);
		void setMax(size_t Max);

		void setInvitaionStatus(bool Status);
		void setTopicStatus(bool Status);
		void setPassWordStatus(bool Status);
		void setAdminStatus(bool Status);

		std::string getName();
		std::string getTopic();
		std::string getPassword();
		size_t		getMax();
		
		bool getInvitaionStatus();
		bool getTopicStatus();
		bool getPassWordStatus();
		bool getAdminStatus();
			
};