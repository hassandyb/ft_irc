/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:03 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/01 22:44:58 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/channel.hpp"

channel::channel()
{
	this->ft_channel_init();
}

void channel::ft_channel_init()
{
		this->InvitaionStatus = false;
		this->TopicStatus = false;
		this->PassWordStatus = false;
		this->AdminStatus = false;
}
// Getters / Setters : -----------------------------

void channel::setName(std::string Name) {this->Name = Name;}
void channel::setTopic(std::string Topic) {this->Topic = Topic;};
void channel::setPassword(std::string Password) {this->Password = Password;}
void channel::setMax(size_t Max) {this->Max = Max;}
void channel::setInvitaionStatus(bool Status) {this->InvitaionStatus = Status;}
void channel::setTopicStatus(bool Status) {this->TopicStatus = Status;}
void channel::setPassWordStatus(bool Status) {this->PassWordStatus = Status;}
void channel::setAdminStatus(bool Status) {this->AdminStatus = Status;}

std::string channel::getName() {return this->Name;}
std::string channel::getTopic() {return this->Topic;}
std::string channel::getPassword() {return this->Password;}
size_t		channel::getMax() {return this->Max;}
bool channel::getInvitaionStatus() {return this->InvitaionStatus;}
bool channel::getTopicStatus() {return this->TopicStatus;}
bool channel::getPassWordStatus() {return this->PassWordStatus;}
bool channel::getAdminStatus() {return this->AdminStatus;}

// utils ----------------------------


void channel::ft_add_member(client & Client) {this->Members.push_back(Client);}
void channel::ft_add_admin(client & Client) {this->Admins.push_back(Client);}
void channel::ft_add_invited(client & Client) {this->Invited.push_back(Client);}


bool channel::ft_find_client(std::string list, std::string Nickname)
{
	std::vector<client >  Container;
	if(list == "Members")
		Container = this->Members;
	if(list == "Admins")
		Container = this->Admins;
	if(list == "Invited")
		Container = this->Invited;
		
	for(size_t i = 0; i < Container.size(); i++)
	{
		if(Container[i].getNickname() == Nickname)
			return true;
	}
	return false;
}

std::string channel::ft_list_admins_and_members()
{
	std::string result;

	for(size_t i = 0; i < Admins.size(); i++)
	{
		result = result + "@" + Admins[i].getNickname() + " ";
	}
	
	for(size_t i = 0; i < Members.size(); i++)
	{
		result = result + Members[i].getNickname() + " ";
	}

	return result;
}

bool channel::ft_a_member_or_admin(std::string Nick)// checks wiether a client is list in the channel admins or members
{
	for(size_t i = 0; i < Members.size(); i++)
	{
		if(Members[i].getNickname() == Nick)
			return true;
	}
	for(size_t i = 0; i < Admins.size(); i++)
	{
		if(Admins[i].getNickname() == Nick)
			return true;
	}
	return false;
}
