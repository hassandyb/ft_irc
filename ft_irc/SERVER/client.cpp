/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:05:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 14:53:22 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/client.hpp"

// Canonical form : --------------------------------

client::client()
{
    this->PassStage = false;
	this->Regestred = false;
    this->Quit = false;
}
client::client(client const & other)
{
    *this = other;
}
client & client::operator=(client const & other)
{
    this->Socket = other.Socket;
    this->Nickname = other.Nickname;
    this->Username = other.Username;
    this->PassStage = other.PassStage;
    this->Regestred = other.Regestred;
    this->Realname = other.Realname;
    this->Quit = other.Quit;

    
    return *this;
}
client::~client() {};

// methods
void client::clearMessage() {this->message.clear();}

// Getters / Setters : --------------------------------

void client::setMessage(std::string message) {this->message += message;}
void client::setSocket(int Socket) { this->Socket = Socket;}
void client::setNickname(std::string Nickname) {this->Nickname = Nickname;}
void client::setUsername(std::string Username) {this->Username = Username;}
void client::setPassStage(bool status) {this->PassStage = status;}
void client::setRegestred(bool status) {this->Regestred = status;}
void client::setRealname(std::string Realname) { this->Realname = Realname;}
void client::setQuit(bool Quit) {this->Quit = Quit;}

std::string client::getMessage() {return this->message;}
int client::getSocket() {return this->Socket;}
std::string client::getNickname(){return this->Nickname;}
std::string client::getUsername() {return this->Username;}
bool client::getPassStage() { return this->PassStage;}
bool client::getRegestred() {return this->Regestred;}
std::string client::getRealname() { return this->Realname;}
bool client::getQuit() {return this->Quit;}
		