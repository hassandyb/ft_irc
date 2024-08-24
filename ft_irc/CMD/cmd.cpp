/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:11 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/26 16:56:07 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/server.hpp"

std::vector<std::string> ft_split_command(std::string Command)
{

    std::vector<std::string> Cmds;

    // no : in the command
    if (Command.find(":") == std::string::npos)
    {
        ft_split_with_spaces(Cmds, Command);
        return Cmds;
    }

    // : exist in our coammnd
    size_t pos = Command.find(":");
    std::string after2points = Command.substr(pos + 1, Command.size() - pos - 1);
    std::string befor2points = Command.substr(0, pos);

    ft_split_with_spaces(Cmds, befor2points);
    Cmds.push_back(after2points);
    return Cmds;
}

bool server::ft_is_registred(client &Client, int Socket)
{
    if (Client.getRegestred() == false)
    {
        std::string msg = ": 451 " + Client.getNickname() + " :You have not registered !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return false;
    }
    return true;
}

void server::ft_execute_command(std::string Command, client &Client, int Socket)
{
    std::vector<std::string> Cmds = ft_split_command(Command);

    if (Cmds.size() == 0)
        return;

    if (Cmds[0] == "PASS" || Cmds[0] == "pass")
    {
        ft_pass(Cmds, Client, Socket);
        return;
    }
    if (Cmds[0] == "USER" || Cmds[0] == "user")
    {
        ft_user(Cmds, Client, Socket);
        return;
    }
    if (Cmds[0] == "NICK" || Cmds[0] == "nick")
    {
        ft_nick(Cmds, Client, Socket);
        return;
    }
    if (Cmds[0] == "QUIT" || Cmds[0] == "quit") 
    {
        ft_quit(Cmds, Client, Socket);
        return ;
    }
        

    if (ft_is_registred(Client, Socket) == false)
        return;

    if (Cmds[0] == "JOIN" || Cmds[0] == "join")
        ft_join(Cmds, Client, Socket);

    else if (Cmds[0] == "INVITE" || Cmds[0] == "invite")
        ft_invite(Cmds, Client, Socket);

    else if (Cmds[0] == "PRIVMSG" || Cmds[0] == "privmsg")
        ft_privmsg(Cmds, Client, Socket);

    else if (Cmds[0] == "MODE" || Cmds[0] == "mode")
        ft_mode(Cmds, Client, Socket);



    else if (Cmds[0] == "TOPIC" || Cmds[0] == "topic")
        ft_topic(Cmds, Client, Socket);

    else if (Cmds[0] == "PART" || Cmds[0] == "part")
        ft_part(Cmds, Client, Socket);
    else if (Cmds[0] == "KICK" || Cmds[0] == "kick")
        ft_kick(Cmds, Client, Socket);

    else if (Cmds[0] == "joke" || Cmds[0] == "JOKE")
    {
        std::string msg = getJoke();
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }
    else
    {

        std::string msg = ": 421 " + Client.getNickname() + " " + Cmds[0] + " :Unknown command\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
    }
}
