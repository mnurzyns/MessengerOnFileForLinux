#include <chrono>

#include <Sender.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <TerminalFunctionality.hpp>

Sender::Sender(const std::string& pathToChatFile, int chatFlag, WINDOW* subwin)
    : chatFilenameWithPath_(pathToChatFile),
      chatFlag_(chatFlag),
      enterMessageWindow_(subwin)
{
    log.info("Sender C-TOR");
}

Sender::~Sender()
{
    log.info("Sender D-TOR");
}

std::unique_ptr<std::string> Sender::getMessageToSend() const
{
    log.info("Sender::getMessageToSend started");
    std::unique_ptr<std::string> rawMessage = getMessageFromStdin();
    std::unique_ptr<std::string> messageToSend = prepareMessageToSend(*rawMessage);
    return messageToSend;
}

bool Sender::sendMessage(const std::string& message) const
{

    bool isMessageSend = FileInterface::Modification::addRow(chatFilenameWithPath_, message);

    if (isMessageSend)
    {
        setNewMessageFlag();
        return true;
    }

    log.info("Sender::sendMessage ERROR: send message fail");
    return false;
}

std::unique_ptr<std::string> Sender::getMessageFromStdin() const
{
    log.info("Sender::getMessageFromStdin started");
    std::unique_ptr<std::string> message = std::make_unique<std::string>();

    int ch = wgetch(enterMessageWindow_);
    while ( ch != '\n' )
    {
        message->push_back( ch );
        ch = wgetch(enterMessageWindow_);
    }

    return message;
}

std::unique_ptr<std::string> Sender::prepareMessageToSend(const std::string& rowMessage) const
{
    if (isTerminalCommand(rowMessage))
    {
        log.info("Sender::prepearMessageToSend Message is a terminal command");
        TerminalFunctionality terminalFunctionality;
        terminalFunctionality.runCommand(rowMessage);
    }

    std::unique_ptr<std::string> message = std::make_unique<std::string>();
    *message = "[" + std::to_string(chatFlag_) + "][" + *getActualDateTime() + "][" + LocalUser::getLocalUser().getUsername() + "][" + rowMessage + "]";

    return message;
}

bool Sender::isTerminalCommand(const std::string& message) const
{
    if (2 > message.size())
    {
        return false;
    }
    if ("//" == std::string(message.begin(), message.begin()+2))
    {
        return true;
    }

    return false;
}

bool Sender::setNewMessageFlag() const
{
    std::string folderName = *FileInterface::Accesor::getFolderName(chatFilenameWithPath_);
    bool isNewFlagCreated = FileInterface::Managment::createFile(folderName + "/NEW");    
    return isNewFlagCreated;
}

std::unique_ptr<std::string> Sender::getActualDateTime() const
{
    std::unique_ptr<std::string> dateTime = std::make_unique<std::string>();
    *dateTime = __DATE__;
    *dateTime += " | " ;
    *dateTime += __TIME__;
    return dateTime;
}
