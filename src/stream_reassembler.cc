#include "stream_reassembler.hh"
#include <vector>
#include <string>
using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity)
{
    this->capacity = capacity;
    this->ack = 0;
    this->eofAfterAck = -1;
}

void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof)
{
    size_t firstUnacceptableIndex = this->ack + this->_output.remaining_capacity();

    // cout << "IDX " << index << endl;
    // cout << "ACK " << this->ack << endl;

    if (index >= firstUnacceptableIndex)
        return;

    if (eof)
        this->eofAfterAck = index + data.size();

    if (index + data.size() <= this->ack)
    {
        if (this->ack == this->eofAfterAck)
            this->_output.end_input();
        return;
    }

    if (this->ack >= index)
    {
        // pushing the characters that are directly insertable into the output buffer
        size_t charsWritten = this->_output.remaining_capacity();
        // cout << "CAS " << data.substr(this->ack - index) << endl;
        this->_output.write(data.substr(this->ack - index));
        charsWritten -= this->_output.remaining_capacity();
        this->ack += charsWritten;
    }
    else
    {
        for (int i = index; i < firstUnacceptableIndex && i < index + data.size(); ++i)
        {
            if (this->eleSet.find(i) == this->eleSet.end())
            {
                this->buffer.push(make_pair(i, data[i - index]));
                this->eleSet.insert(i);
            }
        }
    }

    // adding next adding sequence to output buffer form reassembler buffer
    {
        std::string nextAddingSequence = "";
        size_t charsCanBeWrittenCount = this->_output.remaining_capacity();
        while (!buffer.empty())
        {
            ele x = buffer.top();
            if (x.first < this->ack)
            {
                this->eleSet.erase(x.first);
                this->buffer.pop();
            }
            else if (x.first == this->ack && x.first < firstUnacceptableIndex)
            {
                if (charsCanBeWrittenCount == 0)
                    break;
                nextAddingSequence.push_back(x.second);
                this->eleSet.erase(x.first);
                this->buffer.pop();
                ++this->ack;
                --charsCanBeWrittenCount;
            }
            else
                break;
        }
        // cout << "NAS " << nextAddingSequence << endl;
        this->_output.write(nextAddingSequence);
    }

    if (this->ack == this->eofAfterAck)
        this->_output.end_input();
}

size_t StreamReassembler::unassembled_bytes() const
{
    return this->buffer.size();
}

bool StreamReassembler::empty() const
{
    return this->buffer.empty();
}

size_t StreamReassembler::ack_index() const
{
    return this->ack;
}