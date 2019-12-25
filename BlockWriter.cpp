#include "BlockWriter.h"

BlockWriter::BlockWriter(const std::string &title)
    : m_title (title)
{

}

std::string BlockWriter::title() const
{
    return m_title;
}

