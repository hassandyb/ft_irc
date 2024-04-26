/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:03 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/26 18:49:36 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/channel.hpp"

channel::channel()
{
	this->ft_channel_init();
}


channel::channel(channel const & other)
{
	*this = other;
}
channel & channel::operator=(channel const & other)
{
	if(this != &other)
	{
		this->Name = other.Name;
		this->Topic = other.Topic;
		this->Password = other.Password;
		this->Limit = other.Limit;

		this->PassWordStatus = other.PassWordStatus;
		this->InvitaionStatus = other.InvitaionStatus;
        this->TopicStatus = other.TopicStatus;
        this->AdminStatus = other.AdminStatus;
        this->LimitStatus = other.LimitStatus;
        
        this->Members = other.Members;
        this->Admins = other.Admins;
        this->Invited = other.Invited;
        
        this->Creationtime = other.Creationtime;
        this->Topictime = other.Topictime;
        this->Logtime = other.Logtime;
	}
	return *this;
}
channel::~channel() {};


		
void channel::ft_channel_init()
{
		this->InvitaionStatus = false;
		this->TopicStatus = false;
		this->PassWordStatus = false;
		this->AdminStatus = false;
		this->LimitStatus = false;

		this->Limit = 0;
}
// Getters / Setters : -----------------------------

void channel::setName(std::string Name) {this->Name = Name;}
void channel::setTopic(std::string Topic) {this->Topic = Topic;};
void channel::setPassword(std::string Password) {this->Password = Password;}
void channel::setLimit(size_t Limit) {this->Limit = Limit;}
void channel::setInvitaionStatus(bool Status) {this->InvitaionStatus = Status;}
void channel::setTopicStatus(bool Status) {this->TopicStatus = Status;}
void channel::setPassWordStatus(bool Status) {this->PassWordStatus = Status;}
void channel::setAdminStatus(bool Status) {this->AdminStatus = Status;}
void channel::setLimitStatus(bool Status) {this->LimitStatus = Status;}

std::string channel::getName() {return this->Name;}
std::string channel::getTopic() {return this->Topic;}
std::string channel::getPassword() {return this->Password;}
size_t		channel::getLimit() {return this->Limit;}
bool channel::getInvitaionStatus() {return this->InvitaionStatus;}
bool channel::getTopicStatus() {return this->TopicStatus;}
bool channel::getPassWordStatus() {return this->PassWordStatus;}
bool channel::getAdminStatus() {return this->AdminStatus;}
bool channel::getLimitStatus() {return this->LimitStatus;}




// utils ----------------------------
void channel::ft_add_member(client & Client) {this->Members.push_back(Client);}
void channel::ft_add_admin(client & Client) {this->Admins.push_back(Client);}
void channel::ft_add_invited(client & Client) {this->Invited.push_back(Client);}

std::vector<client > & channel::getMembers() {return Members;}
std::vector<client > & channel::getAdmins() {return Admins;}
std::vector<client > & channel::getInvited() {return Invited;}

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

client & channel::ft_get_client(std::string list, std::string Nickname)
{
	if(list == "Members")
	{
		for(size_t i = 0; i < Members.size(); i++)
		{
			if(Members[i].getNickname() == Nickname)
				return Members[i];
		}
	}
	if(list == "Admins")
	{
		for(size_t i = 0; i < Admins.size(); i++)
		{
			if(Admins[i].getNickname() == Nickname)
				return Admins[i];
		}
	}
	if(list == "Invited")
	{
		for(size_t i = 0; i < Invited.size(); i++)
		{
			if(Invited[i].getNickname() == Nickname)
				return Invited[i];
		}
	}
	// Default return statement that should not be reached
	static client defaultClient;
	return defaultClient;
}

void channel::ft_erase_client(std::string list, std::string Nickname)
{
	if(list == "Members")
	{
		for(size_t i = 0; i < this->Members.size(); i++)
		{
			if(Members[i].getNickname() == Nickname)
				Members.erase(Members.begin() + i);
		}
	}
	if(list == "Admins")
	{
		for(size_t i = 0; i < this->Admins.size(); i++)
		{
			if(Admins[i].getNickname() == Nickname)
				Admins.erase(Admins.begin() + i);
		}
	}
	if(list == "Invited")
	{
		for(size_t i = 0; i < Invited.size(); i++)
		{
			if(Invited[i].getNickname() == Nickname)
				Invited.erase(Invited.begin() + i);
		}
	}
	
}

void channel::ft_add_client(std::string list , client & Client)
{
	if(list == "Members")
		Members.push_back(Client);

	if(list == "Admins")
		Admins.push_back(Client);
		
	if(list == "Invited")
		Invited.push_back(Client);
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

bool channel::ft_a_member_or_admin(std::string Nick)
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
		
size_t channel::ft_channel_size()
{
	size_t i;
	size_t j;

	for(i = 0; i < Members.size(); i++) {}
	for(j = 0; j < Admins.size(); j++) {}

	return i + j;
}

std::string channel::ft_get_mode()
{
	std::string mode;

	if(this->getInvitaionStatus() == true)
		mode = "i";
	if(this->getTopicStatus() == true)
		mode = mode + "t";
	if(this->getPassWordStatus() == true)
		mode = mode + "k";
	if(this->getLimitStatus() == true)
		mode = mode + "l";

	if(mode.empty() == false)
		mode = "+" + mode;
	return mode;
}

void channel::ft_save_creation_time()
{
	this->Creationtime = std::time(NULL);
}

std::string channel::ft_get_creation_time()
{
	std::ostringstream os;
	os << this->Creationtime;
	
	return os.str();
}

void channel::ft_save_topic_time()
{
	this->Topictime = std::time(NULL);
}

std::string channel::ft_get_topic_time()
{
	std::ostringstream os;
	os << this->Topictime;

	return os.str();
}



