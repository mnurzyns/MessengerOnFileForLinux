#include<TerminalControl.hpp>

#include <ChatRequest.hpp>
#include <ConversationControl.hpp>
#include <GlobalVariables.hpp>

#include <iostream>
#include <memory>

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <streambuf>
#include <sstream>


TerminalControl::TerminalControl(ChatStatus chatStatus, std::shared_ptr<ChatInformation> chatInfo)
                                : chatStatus_(chatStatus)
                                , chatInfo_(chatInfo)
{
    // NOOP
}

bool TerminalControl::isWaitingForInvitation = true;
bool TerminalControl::isInvitationExist = false;

bool TerminalControl::waitingInTerminal()
{
    log_.function("TerminalControl::waitingInTerminal()");
    char command[512];
    getstr(command);
    bool commandStatus = terminalFunctionality_.runCommand(std::string(command), chatInfo_);
    return commandStatus;
}

bool TerminalControl::startConversation(const std::string& username, ChatRole chatRole)
{
    log_.function(("ChatControl::startConversation started whit chatRole = " + std::to_string(static_cast<int>(chatRole))).c_str());
    if (ChatRole::inviter == chatRole)
    {
        return startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        return startConversationAsRecipient(username);
    }
}

bool TerminalControl::startConversationAsInviter(const std::string& username)
{
    log_.function("TerminalControl::startConversationAsInviter()");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.sendChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsInviter chatFileWithPath_: " + chatFileWithPath_;
        log_.info(info.c_str());
        chatInfo_->chatPath_ = chatFileWithPath_;
        chatInfo_->messageFlag_ = MessageFlag::inviterMessage;
        return true;
    }
    return false;
}

bool TerminalControl::startConversationAsRecipient(const std::string& username)
{
    log_.function("TerminalControl::startConversationAsRecipient()");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.answerForChatRequest(username, "dupa");
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsRecipient chatFileWithPath_: " + chatFileWithPath_;
        log_.info(info.c_str());
        log_.info("RECEIVER PRZED");
        chatInfo_->chatPath_ = chatFileWithPath_;
        log_.info("RECEIVER PRZED");
        chatInfo_->messageFlag_ = MessageFlag::recipientMessage;
        return true;
    }
    return false;
}


void TerminalControl::lookForInvitation()
{
    while (isWaitingForInvitation)
    {
        auto invitationsFolderContent = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS);
        if (0 == invitationsFolderContent->size())
        {
            sleep(1);
            continue;
        }
        for(auto invitation : *invitationsFolderContent)
        {
            std::string recipent;
            std::string inviter;
            bool getRecipentName = true;

            for (auto letter : invitation)
            {
                if (!getRecipentName)
                {
                    inviter += letter;
                }

                else if ('_' != letter)
                {
                    recipent += letter;
                }

                else if ( '_' == letter)
                {
                    getRecipentName = false;
                }

            }

            if (recipent == getenv("USER"))
            {
                isInvitationExist = true;
                clear();
                printw(("You get an invitation to chat form " + inviter + "\n").c_str());
                printw(("Do you want to chat with this user (start " + inviter + "/n)? \n").c_str());
                printw(">> ");
                refresh();
                isWaitingForInvitation=false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}
