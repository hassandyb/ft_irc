/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:03 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/26 15:21:57 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/channel.hpp"

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





