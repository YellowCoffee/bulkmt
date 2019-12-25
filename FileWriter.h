#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "BlockWriter.h"

class FileWriter : public BlockWriter
{
    static int m_blockCounter;
    static int m_fileWriterCounter;
    int m_id;

    int fibonacci(int n);
    std::string processCommand(const Command& command);
public:
    FileWriter(const std::string& title);
    void write(const Block &block) override;
};

#endif // FILEWRITER_H
