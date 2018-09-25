#include <LoggingOut.hpp>

#include <SignOut.hpp>

LoggingOut::LoggingOut(std::string command)
                : TerminalCommand(command)
{
    //NOOP
}

bool LoggingOut::doCommand()
{
    log_.function("LoggingOut::doCommand()");
    SignOut signOutLocalUser;
    bool commandStatus = false;
    commandStatus = signOutLocalUser.signOutUser();

    std::string logData = "LoggingOut::doCommand() done as " + commandStatus;
    log_.function(logData);

    return commandStatus;
}
