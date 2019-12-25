#include "FileWriter.h"

#include <algorithm>
#include <fstream>

using namespace std;

int FileWriter::m_blockCounter = 0;
int FileWriter::m_fileWriterCounter = 0;

int FileWriter::fibonacci(int n)
{
    if (n == 1)
        return 1;

    if (n < 0)
        return 0;

    return fibonacci(n-1) + fibonacci( n-2);
}

std::string FileWriter::processCommand(const Command &command)
{
    try {
        auto i = stoi( command.line() );
        auto result = fibonacci(i);
        return to_string(result);
    } catch (...) {
        return command.line();
    }
}

FileWriter::FileWriter(const string &title)
    : BlockWriter(title)
{
    m_id = m_fileWriterCounter++;
}

void FileWriter::write(const Block &block)
{
    auto timeStamp = static_cast<int>( block.begin()->timeStamp() );
    char fileName[50];
    sprintf( fileName, "bulk%i_%i_%i.log", timeStamp, m_blockCounter, m_id );
    ofstream out(fileName);
    for_each( block.begin(), block.end(), [this, &out](const auto& command){
        out << this->processCommand( command )<< "\n";
    });
    ++m_blockCounter;
}
