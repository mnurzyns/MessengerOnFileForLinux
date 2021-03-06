#pragma once

#include "TerminalFunctionality.hpp"
#include "TerminalControl.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"

class InviteSender : public TerminalCommand
{
public:
    bool doCommand() const;

    InviteSender(std::string command, std::shared_ptr<ChatInformation> chatInfo);
    ~InviteSender();

    InviteSender(InviteSender &&) = delete;
    InviteSender operator=(InviteSender &&) = delete;
    InviteSender(const InviteSender &) = delete;
    InviteSender operator=(const InviteSender &) = delete;

private:
    std::shared_ptr<ChatInformation> _chatInfo;
    Logger _log {LogSpace::TerminalFunctionality};
};
