/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:08:02 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/26 17:04:04 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

// Canonical form : ----------------




server::server(char * port, char * Password)
{
    this->Port = atoi((const char *)port);
    std::string pass(Password);
    this->Password = pass;

    //remove later
    SerSocketFd = -1;
}



// Setters ---------------------
void server::setSocket(int Socket) {this->Socket = Socket;}
void server::setPort(int Port) {this->Port = Port;}
void server::setPassword(std::string Password) {this->Password = Password;}

// Getters ---------------------
int server::getSocket() {return this->Socket;}
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



// remove later --------------------------------------------------------------------------------------------------


void server::CloseFds()
{
    for(size_t i = 0; i < Clients.size(); i++)
    { //-> close all the Clients
        std::cout << RED << "Client <" << Clients[i].GetFd() << "> Disconnected" << WHI << std::endl;
        close(Clients[i].GetFd());
    }
    if (SerSocketFd != -1)
    { //-> close the server socket
        std::cout << RED << "Server <" << SerSocketFd << "> Disconnected" << WHI << std::endl;
        close(SerSocketFd);
    }
}

void server::ClearClients(int fd)
{ //-> clear the clients
 for(size_t i = 0; i < fds.size(); i++){ //-> remove the client from the pollfd
  if (fds[i].fd == fd)
   {fds.erase(fds.begin() + i); break;}
 }
 for(size_t i = 0; i < Clients.size(); i++){ //-> remove the client from the vector of clients
  if (Clients[i].GetFd() == fd)
   {Clients.erase(Clients.begin() + i); break;}
 }
 close(fd);
}

client & server::ft_get_client_fd(int fd)
{
    size_t i = 0;
    for( i = 0; i < this->Clients.size(); i++)
    {
        if(this->Clients[i].getSocket() == fd)
            return Clients[i];
    }
    return Clients[i];
}

void server::ReceiveNewData(int fd)
{
    std::vector<std::string> cmd;
    char buff[1024]; //-> buffer for the received data
    memset(buff, 0, sizeof(buff)); //-> clear the buffer

    //Client *cli = GetClient(fd);

    client &Client = ft_get_client_fd(fd);
    


    
    ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); //-> receive the data

    if(bytes < 0)
    { //-> check if the client disconnected
        std::cout << RED << "recv fasils "  << WHI << std::endl;
        // ClearClients(fd); //-> clear the client
        // close(fd); //-> close the client socket
    }

    else
    { 
        //-> print the received data
        // trasform buff to string 
        Client.setBuffer(buff);

        // if(Client.getBuffer().find_first_of("\r\n") == std::string::npos)
		// 	return;
        if(Client.getBuffer().find_first_of("\n") == std::string::npos)
			return;


        // std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;
        // std::string str(buff);
        ft_execute_command(buff, Client, fd);
        Client.clearBuffer();
        // std::cout << Client.getBuffer() << std::endl;
        //here you can add your code to process the received data: parse, check, authenticate, handle the command, etc...
    }
}



void server::AcceptNewClient()
{
    client cli; //-> create a new client
    struct sockaddr_in cliadd;
    struct pollfd NewPoll;
    socklen_t len = sizeof(cliadd);

    int incofd = accept(SerSocketFd, (sockaddr *)&(cliadd), &len); //-> accept the new client
    if (incofd == -1)
    {std::cout << "accept() failed" << std::endl; return;}

    if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
    {std::cout << "fcntl() failed" << std::endl; return;}

    NewPoll.fd = incofd; //-> add the client socket to the pollfd
    NewPoll.events = POLLIN; //-> set the event to POLLIN for reading data
    NewPoll.revents = 0; //-> set the revents to 0

    cli.SetFd(incofd); //-> set the client file descriptor
    cli.setIpAdd(inet_ntoa((cliadd.sin_addr))); //-> convert the ip address to string and set it
    Clients.push_back(cli); //-> add the client to the vector of clients
    fds.push_back(NewPoll); //-> add the client socket to the pollfd

    std::cout << GRE << "Client <" << incofd << "> Connected" << WHI << std::endl;
}


void server::SerSocket()
{
    int en = 1;
    struct sockaddr_in add;
    struct pollfd NewPoll;
    add.sin_family = AF_INET; //-> set the address family to ipv4
    add.sin_addr.s_addr = INADDR_ANY; //-> set the address to any local machine address
    add.sin_port = htons(this->Port); //-> convert the port to network byte order (big endian)

    SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //-> create the server socket
    if(SerSocketFd == -1) //-> check if the socket is created
    throw(std::runtime_error("faild to create socket"));

    if(setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1) //-> set the socket option (SO_REUSEADDR) to reuse the address
    throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
    if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
    throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
    if (bind(SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1) //-> bind the socket to the address
    throw(std::runtime_error("faild to bind socket"));
    if (listen(SerSocketFd, SOMAXCONN) == -1) //-> listen for incoming connections and making the socket a passive socket
    throw(std::runtime_error("listen() faild"));

    NewPoll.fd = SerSocketFd; //-> add the server socket to the pollfd
    NewPoll.events = POLLIN; //-> set the event to POLLIN for reading data
    NewPoll.revents = 0; //-> set the revents to 0
    fds.push_back(NewPoll); //-> add the server socket to the pollfd
}



