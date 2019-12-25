#ifndef BLOCKBUILDER_H
#define BLOCKBUILDER_H

#include <memory>

#include "Block.h"
#include "BlockWriter.h"

class Terminator;
class DynamicTerminator;
class RegularTerminator;

typedef void(*WriteCallback)(const Block& block) ;

class BlockBuilder
{
public:
    BlockBuilder();

    void insertCommand(const Command& command);
    void setBlockSize(int blockSize);
    Block getBlock();
    void subscribe(const std::shared_ptr<BlockWriter> &blockWriter);
    void subscribe( WriteCallback callback );

    void setTerminator(const std::shared_ptr<Terminator>& terminator);

private:
    std::list<Command> m_commands;
    std::list<std::weak_ptr<BlockWriter>> m_blockWriters;
    WriteCallback m_callback;
    std::shared_ptr<Terminator> m_terminator;
};

class Terminator {
public:
    Terminator (BlockBuilder* builder)
        : m_builder(builder) {}
    virtual bool checkFinish(const Command& command) = 0;

protected:
    BlockBuilder* m_builder;
};

class RegularTerminator : public Terminator {
public:
    RegularTerminator(BlockBuilder* builder)
        : Terminator(builder) {}

    bool checkFinish(const Command &command) override;

    static void setCommandSize(int value) {
        commandSize = value;
    }
private:
    static int commandSize;
    int commandCount = 0;
};

class DynamicTerminator : public Terminator {
public:
    DynamicTerminator(BlockBuilder* builder)
        : Terminator(builder) {}

    bool checkFinish(const Command &command) override;

private:
    int m_counter = 0;
};

#endif // BLOCKBUILDER_H

