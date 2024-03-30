#include "tcp_receiver.hh"

#include <algorithm>

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg)
{
    const TCPHeader header = seg.header();

    this->_synReceived = this->_synReceived || header.syn;
    this->_isn = (header.syn) ? header.seqno : this->_isn;

    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t absoluteSequenceNumber = unwrap(header.seqno, _isn, checkpoint);
    uint64_t streamIndex = absoluteSequenceNumber - _synReceived;
    std::string message = std::string(seg.payload().str());

    this->_reassembler.push_substring(message, streamIndex, false);

    this->_finReceived = this->_finReceived || header.fin;
    if (header.fin)
        this->stream_out().end_input();
}

optional<WrappingInt32> TCPReceiver::ackno() const
{
    if (this->_synReceived)
    {
        uint64_t streamIndex = this->_reassembler.ack_index();
        uint64_t absoluteSequenceNumber = streamIndex + 1 + this->_finReceived;
        return wrap(absoluteSequenceNumber, this->_isn);
    }
    return {};
}

size_t TCPReceiver::window_size() const
{
    return this->stream_out().remaining_capacity();
}
