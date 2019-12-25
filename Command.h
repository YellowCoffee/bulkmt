#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <ostream>
#include <ctime>

class Command
{
public:
    enum class CommandType: int {
        Line = 0,
        OpenBrace,
        CloseBrace,
        Eof
    };

    Command(const std::string& line );
    Command(CommandType type);

    std::string line() const;
    std::time_t timeStamp() const;
    CommandType commandType() const;

    friend std::ostream &operator<<(std::ostream &os, const Command &command);

private:
    std::string m_line;
    std::time_t m_timeStamp;
    CommandType m_commandType = CommandType::Line;
};

#endif // COMMAND_H