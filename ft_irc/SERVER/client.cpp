/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:05:40 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/27 18:14:33 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/client.hpp"

// Canonical form : --------------------------------

client::client()
{
    this->registred = false;
}


// Getters / Setters : --------------------------------

void client::setSocket(int Socket) { this->Socket = Socket;}
void client::setNickname(std::string Nickname) {this->Nickname = Nickname;}
void client::setUsername(std::string Username) {this->Username = Username;}
int client::getSocket() {return this->Socket;}
std::string client::getNickname(){return this->Nickname;}
std::string client::getUsername() {return this->Username;}


