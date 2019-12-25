#include "ConsoleWriter.h"

#include <iostream>
#include <iterator>

#include <thread>

using namespace std;

unsigned int ConsoleWriter::factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial( n-1 );
}

std::string ConsoleWriter::processCommand(const Command &command)
{
    try {
        auto i = std::stoi( command.line() );
        auto result = factorial(i);
        return to_string(result);
    } catch (...) {
        return command.line();
    }
}

void ConsoleWriter::printBlock(const Block &block)
{
    std::lock_guard<std::mutex> lg( m_coutMutex );
    cout << "bulk: ";
    auto it = block.begin();
    cout << processCommand( *it++ );
    while (it != block.end()) {
        cout << ", " << processCommand(*it++);
    }
    cout << endl;
}

ConsoleWriter::ConsoleWriter(const string &title)
    : BlockWriter(title)
{

}

void ConsoleWriter::write(const Block &block)
{
    thread t( printBlock, this, block );
    t.join();
}
