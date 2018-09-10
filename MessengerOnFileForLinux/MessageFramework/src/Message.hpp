#pragma once

#include <ChatData.hpp>

class Message
{
public:
    bool setChatRole();
    bool setDate();
    bool setTime();
    bool setUsername();
    bool setMessage();

    ChatRole getChatRole();
    std::string getDate();
    std::string getTime();
    std::string getUsername();
    std::string getMessage();

    Message();
    ~Message();

private:
    ChatRole chatRole_;
    std::string date_;
    std::string time_;
    std::string username_;
    std::string message_;

};

// [1][Jul 31 2018 | 09:19:13][tomek][czesc, co u ciebie ?]
