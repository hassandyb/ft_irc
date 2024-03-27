/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:08:02 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/03/27 18:14:02 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// Canonical form : ----------------




server::server(char * port, char * Password)
{

    this->Port = atoi((const char *)port);
    std::string pass(Password);
    this->Password = pass;

}



// Setters ---------------------
void server::setSocket(int Socket) {this->Socket = Socket;}
void server::setPort(int Port) {this->Port = Port;}
void server::setPassword(std::string Password) {this->Password = Password;}

// Getters ---------------------
int server::getSocket() {return this->Socket;}
int server::getPort() {return this->Port;}
std::string server::getPassword() {return this->Password;}








