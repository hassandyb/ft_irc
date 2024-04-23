

#include "../HEADERS/server.hpp"

std::vector<channel> & getChannels()
{
    static std::vector<channel> Channels;
    return Channels;
}

// channel & ft_get_channel(std::string name)
// {
//     std::vector<channel> Channels = getChannels();
//     for(size_t i = 0; i < Channels.size(); i++)
//     {
//         if(Channels[i].getName() == name)
//             return Channels[i];
//     }
//     throw std::invalid_argument("Channel not found");
// }

void server::ft_topic(std::vector<std::string> Cmds, client & Client, int Socket)
{
    // TOPIC <channel> <topic>
    

    

    if(Cmds.size() == 1)
    {
        std::string msg = ": 461 " + Client.getNickname() + " :Not enough parameters !\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
        // topic #group :Friends food
    if(ft_find_a_channel(Cmds[1]) == false)
    {
        std::string msg = ": 403 " + Client.getNickname() + " " + Cmds[1] + " :No such channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    // 3  caes jst 2 args
    channel Channel = ft_get_a_channel(Cmds[1]);

    if(Channel.ft_a_member_or_admin(Client.getNickname()) == false)
    {
        std::string msg = ": 442 " + Channel.getName() + " :You're not on that channel\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }

    if(Cmds.size() == 2 || Channel.getTopic().empty() == true)
    {
        std::string msg = ": 331 " + Client.getNickname() + " " + Cmds[1] + " :No topic is set\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;

    }
    if(Cmds.size() == 2 || Channel.getTopic().empty() == false)
    {
        std::string msg = ": 332 " + Client.getNickname() + " " + Channel.getName() + " :" + Channel.getTopic() + "\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0); 
        Channel.ft_save_topicTime();
        std::string msg1 = ": 333 " + Client.getNickname() + " " + Channel.getName() + " " + Client.getNickname() + Channel.getTopicTime() + "\r\n"; 
        ft_send(Socket, msg1.c_str(), msg1.size(), 0);
        return ;
    }

    if(Channel.getTopicStatus() == true && Channel.ft_find_client("Admins", Client.getNickname()) == false)
    {
        std::string msg = ": 482 " + Channel.getName() + " :You're not a channel operator\r\n";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }


    // :a!a@localhost TOPIC #chaimaa newtopic
    // toic #group food ...
    Channel.setTopic(Cmds[2]);
    std::string msg = ":" + Client.getNickname() + "!" + Client.getUsername() + "@localhost TOPIC " + Channel.getName() + " " + Channel.getTopic();
    //   change topic 



    // if(ft_find_a_channel(Cmds[1]) == false)
    // {
    //     std::string msg = Client.getNickname() + " TOPIC (403) :No such channel";
    //     ft_send(Socket, msg.c_str(), msg.size(), 0);
    //     return ;
    // }
    // channel & Channel = ft_get_a_channel(Cmds[1]);
    // if(Channel.getTopic().empty() == true)
    // {
    //     std::string msg = Client.getNickname() + " TOPIC " + Cmds[1] + " :No topic is set";
    //     ft_send(Socket, msg.c_str(), msg.size(), 0);
    //     return ;
    // }
    // std::string msg = Client.getNickname() + " TOPIC " + Cmds[1] + " :" + Channel.getTopic();
    // ft_send(Socket, msg.c_str(), msg.size(), 0);
}