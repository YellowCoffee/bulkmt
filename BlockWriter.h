#ifndef BLOCKWRITER_H
#define BLOCKWRITER_H

#include "Block.h"

class BlockWriter
{
    std::string m_title;
public:
    BlockWriter(const std::string& title);
    virtual ~BlockWriter() = default;

    virtual void write(const Block& block) = 0;
    std::string title() const;
};

#endif // BLOCKWRITER_H
