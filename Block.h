#ifndef BLOCK_H
#define BLOCK_H

#include <list>
#include <string>

#include "Command.h"

class Block
{
public:
    Block( const std::list<Command>& commandVector );
    std::list<Command>::const_iterator begin() const;
    std::list<Command>::const_iterator end() const;
    int commandCount() const;

    time_t timeStamp() const;

private:
    std::list<Command> m_commandVector;
};


#endif // BLOCK_H
