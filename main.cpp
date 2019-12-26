#include <iostream>
#include <sstream>
#include <algorithm>

#include "BlockBuilder.h"
#include "ParallelFileWriter.h"
#include "ConsoleWriter.h"


#include <thread>

using namespace std;

int line_counter = 0;
int m_blockCounter = 0;
int m_commandCounter = 0;

/*
void processBlock(const Block& block) {
    ++m_blockCounter;
    m_commandCounter += block.commandCount();
}

void printSatistic() {
    std::cout << "main line count: " << line_counter
              << "; command count: " << m_commandCounter
              << "; block count: " << m_blockCounter;
}
*/

void process(std::shared_ptr<BlockWriter> &&writer, std::queue<Block> &queue)
{
    while ( !m_quit ){
        std::unique_lock<std::mutex> lk(m_mutex);
        m_conditionVariable.wait( lk, [&queue, this](){
            return !queue.empty() || m_quit;
        } );

        if ( !queue.empty() ) {
            auto block = queue.front();
            queue.pop();
            writer->write( block );
            lk.unlock();
        }
    }
}


int main(int argc, char *argv[])
{


/*
    BlockBuilder blockBuilder;
    if (argc == 2) {
        int i;
        try {
            i = std::stoi( argv[1] );
            blockBuilder.setBlockSize(i);
        } catch (...) {

        }
    }

    auto consoleWriter = make_shared<ConsoleWriter>("log");
    auto parallelFileWriter = make_shared<ParallelFileWriter>();

    blockBuilder.subscribe( consoleWriter );
    blockBuilder.subscribe( parallelFileWriter );
    blockBuilder.subscribe( processBlock );

    string line;
    while ( getline(std::cin, line) ) {
        blockBuilder.insertCommand( line );
        ++line_counter;
    }
    blockBuilder.insertCommand( Command::CommandType::Eof );

    printSatistic();
*/
    return 0;
}

