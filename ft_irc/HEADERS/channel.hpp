/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:43 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/26 18:22:04 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"
#include <iostream>
#include <vector>
#include <sstream> 

class client;

class channel
{
	private :
		std::string Name;
		std::string Topic;
		std::string Password;
		size_t		Limit;

		bool PassWordStatus;
		bool InvitaionStatus;
		bool TopicStatus;
		bool AdminStatus;
		bool LimitStatus;		//l: Set/remove the user limit to channel

		std::vector<client > Members;
		std::vector<client > Admins;
		std::vector<client > Invited;

		time_t Creationtime;
		time_t Topictime;
		time_t Logtime;
			
	public :
		channel();
		channel(channel const & other);
		channel & operator=(channel const & other);
		~channel();
		void ft_channel_init();

		
		
		// Getters / Setters ------------------
		void setName(std::string Name);
		void setTopic(std::string Topic);
		void setPassword(std::string Password);
		void setLimit(size_t Limit);
		
		void setInvitaionStatus(bool Status);
		void setTopicStatus(bool Status);
		void setPassWordStatus(bool Status);
		void setAdminStatus(bool Status);
		void setLimitStatus(bool Status);
		
		std::string getName();
		std::string getTopic();
		std::string getPassword();
		size_t		getLimit();
		
		bool getInvitaionStatus();
		bool getTopicStatus();
		bool getPassWordStatus();
		bool getAdminStatus();
		bool getLimitStatus();
		

		// utilts -----------------
		
		void ft_add_member(client & Client);
		void ft_add_admin(client & Client);
		void ft_add_invited(client & Client);
		
		std::vector<client > & getMembers();
		std::vector<client > & getAdmins();
		std::vector<client > & getInvited();

		
		bool ft_find_client(std::string list, std::string Nickname);// list == Members, admins, ...ext  return -1 if do no exist , return indice of it if it exist 
		client & ft_get_client(std::string list, std::string Nickname);
		void ft_erase_client(std::string list, std::string Nickname);
		void ft_add_client(std::string list , client & Client);
		
		std::string ft_list_admins_and_members();
		bool ft_a_member_or_admin(std::string Nick);
		size_t ft_channel_size();
		std::string ft_get_mode();
		
		void ft_save_creation_time();
		std::string ft_get_creation_time();
		void ft_save_topic_time();
		std::string ft_get_topic_time();



		// only for testing ....
		void SerSocket();
		
};