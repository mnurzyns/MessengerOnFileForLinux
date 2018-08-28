#include<TerminalControl.hpp>

#include <ChatRequest.hpp>
// REMEMBER TO ADD THIS FILE INTO TEST CMAKELISTS

void TerminalControl::startConversation(const std::string& username, ChatRole chatRole)
{
    log.info(("ChatControl::startConversation started whit chatRole = " + std::to_string(static_cast<int>(chatRole))).c_str());
    if (ChatRole::inviter == chatRole)
    {
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        startConversationAsRecipient(username);
    }
}

void TerminalControl::startConversationAsInviter(const std::string& username)
{
    log.info("ChatControl::startConversationAsInviter started");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.sendChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsInviter chatFileWithPath_: " + chatFileWithPath_;
        log.info(info.c_str());
        messageFlag_ = MessageFlag::inviterMessage;
        //conversation(); // TO DO mnurzyns zwraca boola i gdzie indziej obsluga converstaion()
    }/*
    else
    {
        conversationEpilog();
    }*/
}

void TerminalControl::startConversationAsRecipient(const std::string& username)
{
    log.info("ChatControl::startConversationAsRecipient started");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.answerForChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsRecipient chatFileWithPath_: " + chatFileWithPath_;
        log.info(info.c_str());
        messageFlag_ = MessageFlag::recipientMessage;
        //conversation(); // TO DO mnurzyns zwraca boola i gdzie indziej obsluga converstaion()
    }/*
    else
    {
        conversationEpilog();
    }*/
}
