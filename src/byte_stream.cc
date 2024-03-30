#include "byte_stream.hh"
#include <iostream>
using namespace std;

ByteStream::ByteStream(const size_t capacity)
{
    this->capacity = capacity;
    this->totalBytesWritten = 0;
    this->totalBytesPopped = 0;
    this->isInputEnded = false;
}

size_t ByteStream::write(const string &data)
{
    size_t pointer = 0;
    while (this->remaining_capacity() > 0 && pointer < data.size())
    {
        this->dq.push_back(data[pointer]);
        ++pointer;
    }
    this->totalBytesWritten += pointer;
    return pointer;
}

size_t ByteStream::remaining_capacity() const
{
    return this->capacity - this->dq.size() + this->input_ended();
}

void ByteStream::end_input()
{
    this->isInputEnded = true;
    this->dq.push_back((char)EOF_CHAR);
}

string ByteStream::peek_output(const size_t len)
{
    // not enough bytes to unpack; expected value <= len(this->dq)
    if (len > this->dq.size())
        this->set_error();
    int pointer = 0;
    string data = "";
    for (char ch : this->dq)
    {
        if (pointer == len || ((int)ch == EOF_CHAR && this->isInputEnded))
            break;
        data.push_back(ch);
        ++pointer;
    }
    return data;
}

void ByteStream::pop_output(const size_t len)
{
    // not enough bytes to unpack; expected value <= len(this->dq)
    if (len > this->dq.size())
        this->set_error();
    int pointer = 0;
    while (!this->dq.empty() && pointer < len)
    {
        this->dq.pop_front();
        ++pointer;
    }
    this->totalBytesPopped += len;
}

string ByteStream::read(const size_t len)
{
    string data = this->peek_output(len);
    this->pop_output(len);
    return data;
}

bool ByteStream::input_ended() const
{
    if (this->dq.empty())
        return false;
    return (int)this->dq.back() == EOF_CHAR && this->isInputEnded;
}

bool ByteStream::eof() const
{
    return (int)this->dq.front() == EOF_CHAR && this->isInputEnded;
}

size_t ByteStream::buffer_size() const
{
    return this->dq.size() - this->input_ended();
}

bool ByteStream::buffer_empty() const
{
    return this->buffer_size() == 0;
}

size_t ByteStream::bytes_written() const
{
    return this->totalBytesWritten;
}
size_t ByteStream::bytes_read() const
{
    return this->totalBytesPopped;
}