#include "Command.h"

#include <iostream>

Command::Command(const std::string &line)
    : m_line(line)
{
    if (line.compare("{") == 0) {
        m_commandType = CommandType::OpenBrace;
    } else if ( line.compare("}") == 0) {
        m_commandType = CommandType::CloseBrace;
    } else {
        m_commandType = CommandType::Line;
    }
    m_timeStamp = std::time(nullptr);
}

Command::Command(Command::CommandType type)
{
    m_commandType = type;
    m_line = "";
}

std::string Command::line() const
{
    return m_line;
}

std::time_t Command::timeStamp() const
{
    return m_timeStamp;
}

Command::CommandType Command::commandType() const
{
    return m_commandType;
}

std::ostream& operator<<(std::ostream &os, const Command &command)
{
    return os << command.line();
}

