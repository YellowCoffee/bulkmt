#include "BlockBuilder.h"

int RegularTerminator::commandSize = 3;

BlockBuilder::BlockBuilder()
{
    m_terminator = std::make_shared<RegularTerminator>(this);
}

void BlockBuilder::insertCommand(const Command &command)
{
    if (command.commandType() == Command::CommandType::Line)
        m_commands.push_back( command );

    if ( m_terminator->checkFinish(command) ) {
        if (m_commands.empty())
            return;

        Block block( m_commands );
        for(const auto& blockWriter : m_blockWriters) {
            if (auto ptr = blockWriter.lock())
                ptr->write(block);
        }

        m_callback(block);

        m_commands.clear();
    }
}

void BlockBuilder::setBlockSize(int blockSize)
{
    RegularTerminator::setCommandSize( blockSize );
}

void BlockBuilder::subscribe(const std::shared_ptr<BlockWriter>& blockWriter)
{
    m_blockWriters.push_back( std::weak_ptr<BlockWriter>( blockWriter ));
}

void BlockBuilder::subscribe(WriteCallback callback)
{
    m_callback = callback;
}

void BlockBuilder::setTerminator(const std::shared_ptr<Terminator> &terminator)
{
    m_terminator = terminator;
}

bool RegularTerminator::checkFinish(const Command &command)
{
    switch (command.commandType()) {
    case Command::CommandType::OpenBrace: {
        auto terminator = std::make_shared<DynamicTerminator>(m_builder);
        m_builder->setTerminator( terminator );
        return terminator->checkFinish(command);
    }
    case Command::CommandType::Eof:
        return true;
    default:
        break;
    }

    if (++commandCount == commandSize) {
        commandCount = 0;
        return true;
    }
    return false;
}

bool DynamicTerminator::checkFinish(const Command &command)
{
    switch (command.commandType()) {
    case Command::CommandType::OpenBrace:
        if ( m_counter++ == 0)
            return true;
        return false;
    case Command::CommandType::CloseBrace:
        --m_counter;
        if ( m_counter == 0 ) {
            auto terminator = std::make_shared<RegularTerminator>(m_builder);
            m_builder->setTerminator( terminator );
            return true;
        }
    default:
        break;
    }
    return false;
}
