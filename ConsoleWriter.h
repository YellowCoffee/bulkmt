#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

#include <mutex>

#include "BlockWriter.h"

class ConsoleWriter : public BlockWriter
{
    std::mutex m_coutMutex;


    unsigned int factorial(int n);
    std::string processCommand(const Command& command);
    void printBlock( const Block &block );

public:
    ConsoleWriter(const std::string& title);
    void write(const Block &block) override;
};

#endif // CONSOLEWRITER_H
