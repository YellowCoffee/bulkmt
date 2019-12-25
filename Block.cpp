#include "Block.h"

Block::Block(const std::list<Command> &commandVector)
    : m_commandVector(commandVector)
{

}

std::list<Command>::const_iterator Block::begin() const
{
    return m_commandVector.cbegin();
}

std::list<Command>::const_iterator Block::end() const
{
    return m_commandVector.cend();
}

int Block::commandCount() const
{
    return m_commandVector.size();
}

std::time_t Block::timeStamp() const
{
    return m_commandVector.front().timeStamp();
}