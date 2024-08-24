/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:08:02 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/27 14:57:39 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"
#include "../HEADERS/client.hpp"
// Canonical form : ----------------




server::server(char * port, char * Password)
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi((const char *)port));
    /////
    this->Port = atoi((const char *)port);
    std::string pass(Password);
    this->Password = pass;

}



// Setters ---------------------
void server::setSocket(int Socket) {this->socketFd = Socket;}
void server::setPort(int Port) {this->Port = Port;}
void server::setPassword(std::string Password) {this->Password = Password;}

// Getters ---------------------
int server::getSocket() {return this->socketFd;}
int server::getPort() {return this->Port;}
std::string server::getPassword() {return this->Password;}




// Utils -----------------------------------

bool server::ft_find_a_client(std::string Nick)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getNickname() == Nick)
            return true;
    }
    return false;
}

bool server::ft_find_a_channel(std::string Channel_name)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel_name)
            return true;
    }
    return false;
}

channel & server::ft_get_a_channel(std::string Channel_name)
{
    size_t i = 0;
    for(i = 0 ; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel_name)
            return Channels[i];
    }
    return Channels[i]; 
}

client & server::ft_get_client(std::string nick)
{
    size_t i ;
    for( i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getNickname() == nick)
            return Clients[i];
    }
    return Clients[i];
}

void server::ft_delete_client(client Client)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getNickname() == Client.getNickname())
        {
            Clients.erase(Clients.begin() + i);
            return ;
        }
    }
}
void server::ft_delete_client(int sock)
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        if(Clients[i].getSocket() == sock)
        {
            Clients.erase(Clients.begin() + i);
            return ;
        }
    }
}

void server::ft_delete_channel(std::string Channel_name)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel_name)
            Channels.erase(Channels.begin() + i);
    }
}

void server::ft_close_all_socket()
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        std::cout << Clients[i].getNickname() << " : Disconnected" << std::endl;
        close(Clients[i].getSocket());
        fds.erase(fds.begin() + i);
    }
    std::cout << "Sever Disconnected" << std::endl;
    close(socketFd);
}



/// methods

std::string server::read_from_client(int client_index)
{
    char buffer[1024];
    bzero(buffer, sizeof(buffer));
    int valread = read(fds[client_index].fd, buffer, sizeof(buffer) - 1);
    buffer[valread] = '\0';

    // check is there new line
    if (valread == 0)
    {
        // Client disconnected
        close(fds[client_index].fd);
        fds.erase(fds.begin() + client_index);
        Clients.erase(Clients.begin() + client_index - 1);
        throw std::runtime_error("Client disconnected");
    }
    return std::string(buffer);
}

void server::start()
{
    unsigned int sockaddr_in_size = sizeof(address);
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
        throw std::runtime_error("Error creating socket");

    int opt = 1;
    int setsockoptStatus = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (setsockoptStatus == -1)
        throw std::runtime_error("Error setting socket options");
    
    int bindStatus = bind(socketFd, (struct sockaddr *)&address, sockaddr_in_size);
    if (bindStatus == -1)
        throw std::runtime_error("Error binding socket");

    int listenStatus = listen(socketFd, SOMAXCONN);
    if (listenStatus == -1)
        throw std::runtime_error("Error listening socket");

    struct pollfd server_fd;
    server_fd.fd = socketFd;
    server_fd.events = POLLIN;
    fds.push_back(server_fd);

    while (true)
    {
        int pollStatus = poll(&fds.front(), fds.size(), -1);
        if (pollStatus == -1)
            throw std::runtime_error("Error polling socket");
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == socketFd)
                {
                    // Accept a new connection
                    client addClient;
                    int newSocketFd = accept(socketFd, (struct sockaddr *)&address, &sockaddr_in_size);
                    if (newSocketFd == -1)
                        throw std::runtime_error("Error accepting connection");
                    ////
                    struct pollfd newClient;
                    newClient.fd = newSocketFd;
                    newClient.events = POLLIN;
                    fds.push_back(newClient);
                    ////
                    addClient.setSocket(newSocketFd);
                    Clients.push_back(addClient);
                    std::cout << "New client connected" << std::endl;
                }
                else
                {
                    try
                    {
                        client &currentClient = Clients[i - 1];

                        currentClient.setMessage(read_from_client(i));
                        std::string message = currentClient.getMessage();

                        if (message.find('\n') != std::string::npos)
                        {
                            ft_execute_command(message, currentClient, fds[i].fd);
                            currentClient.clearMessage();
                            if(currentClient.getQuit() == true)
                            {
                                close(currentClient.getSocket());
                                ft_delete_client(currentClient);
                                fds.erase(fds.begin() + i);
                            }
                        }

                    }
                    catch (const std::runtime_error &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }
    }
}