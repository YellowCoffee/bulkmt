#ifndef PARALLELFILEWRITER_H
#define PARALLELFILEWRITER_H

#include "BlockWriter.h"

#include <atomic>
#include <queue>
#include <thread>
#include <condition_variable>

class ParallelFileWriter : public BlockWriter
{
public:
    ParallelFileWriter();
    ~ParallelFileWriter();

    void write(const Block &block) override;

private:
    std::mutex m_mutex;
    std::queue<Block> m_blockQueue;
    std::condition_variable m_conditionVariable;
    std::thread m_thread1;
    std::thread m_thread2;
    std::atomic_bool m_quit;

    void process(std::shared_ptr<BlockWriter> &&writer, std::queue<Block>& queue);
};

#endif // PARALLELFILEWRITER_H