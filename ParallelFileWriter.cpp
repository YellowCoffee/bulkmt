#include "ParallelFileWriter.h"
#include "FileWriter.h"

#include <memory>
#include <functional>

#include <iostream>

ParallelFileWriter::ParallelFileWriter()
    : BlockWriter("ParallelFileWriter")
{
    m_quit = false;
    m_thread1 = std::thread( process, this, std::make_shared<FileWriter>("file1"), std::ref(m_blockQueue) );
    m_thread2 = std::thread( process, this, std::make_shared<FileWriter>("file2"), std::ref(m_blockQueue) );
}

ParallelFileWriter::~ParallelFileWriter()
{
    m_quit = true;
    m_conditionVariable.notify_all();
    m_thread1.join();
    m_thread2.join();
}

void ParallelFileWriter::write(const Block &block)
{
    m_blockQueue.emplace(block);
    m_conditionVariable.notify_one();
}

void ParallelFileWriter::process(std::shared_ptr<BlockWriter> &&writer, std::queue<Block> &queue)
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

