#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>
#include <mutex>

#include <Sender.hpp>
#include <Receiver.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>
#include <Message.hpp>
#include <TerminalFunctionality.hpp>
#include "UserInactivityDetector.hpp"

class ConversationControl
{
public:
    void conversation();
    void conversationEpilog();

    ConversationControl(std::shared_ptr<ChatInformation> chatInfo);
    ~ConversationControl();

    ConversationControl(ConversationControl &&) = delete;
    ConversationControl operator=(ConversationControl &&) = delete;
    ConversationControl(const ConversationControl &) = delete;
    ConversationControl operator=(const ConversationControl &) = delete;

    static bool isConversationRunning_;

private:
    void getMessage();
    bool isMessagesToReadExist();
    void handleInterlocutorInactivity();
    void markUserInactivityAsHandled();
    void reciveMessage();
    void sendMessage();
    void stopThreads();
    void startThreads();
    void saveMessageToDisplay();

    std::unique_ptr<std::thread> getMessageToQueueThread_;
    std::unique_ptr<std::thread> sendMessageFromQueueThread_;
    std::unique_ptr<std::thread> reciveMessageThread_;
    std::unique_ptr<Receiver> receiver_;
    std::unique_ptr<Sender> sender_;
    std::shared_ptr<ChatInformation> chatInfo_;
    std::queue<Message> messageReadyToSend_;
    std::queue<PurgeMessage> messageToDisplay_;
    bool isThreadsRunning_;
    bool isUserInactivityWasHandled_;
    UserInactivityDetector userInactivityDetector_;
    std::once_flag userInactivityWasHandled_;

    Logger log_{LogSpace::ChatStarter};
};
