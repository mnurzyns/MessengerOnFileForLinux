#pragma once

#include <memory>

#include "Logger.hpp"
#include "LogSpace.hpp"

enum class ChatRole
{
    inviter,
    recipient
};

class Message
{
public:
    std::string messageToSave() const;

    std::string getTime() const;
    std::string getUsername() const;
    std::string getContent() const;

    Message(std::string messageFlag, std::string username, std::string content);
    Message(std::string fullMessageInRow);
    virtual ~Message() = default;
    Message(Message &&) = default;
    Message& operator=(Message &&) = default;
    Message(const Message &) = default;
    Message& operator=(const Message &) = default;

protected:
    std::string _time;
    std::string _username;
    std::string _content;

    Message() = default;

private:
    bool setMessageFlag(std::string messageFlag);
    bool setContent(std::string content);

    std::string _messageFlag;

    Logger _log {LogSpace::MessageFramework};
};

// [1][Tue Oct 16 08:16:55 2018][mnurzyns][czesc, co u ciebie ?]
