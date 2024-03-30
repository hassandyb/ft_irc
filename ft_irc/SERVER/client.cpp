/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:05:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/30 09:19:00 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/client.hpp"

// Canonical form : --------------------------------

client::client()
{
    this->PassStage = false;
	this->Regestred = false;
}


// Getters / Setters : --------------------------------

void client::setSocket(int Socket) { this->Socket = Socket;}
void client::setNickname(std::string Nickname) {this->Nickname = Nickname;}
void client::setUsername(std::string Username) {this->Username = Username;}
void client::setPassStage(bool status) {this->PassStage = status;}
void client::setRegestred(bool status) {this->Regestred = status;}
void client::setRealname(std::string Realname) { this->Realname = Realname;}
	
int client::getSocket() {return this->Socket;}
std::string client::getNickname(){return this->Nickname;}
std::string client::getUsername() {return this->Username;}
bool client::getPassStage() { return this->PassStage;}
bool client::getRegestred() {return this->Regestred;}
std::string client::getRealname() { return this->Realname;}
		