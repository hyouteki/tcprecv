#ifndef CRAPPY_STREAM_REASSEMBLER_HH_
#define CRAPPY_STREAM_REASSEMBLER_HH_

#include "byte_stream.hh"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

typedef pair<uint64_t, char> ele;

/*
 * @desc: a class that assembles a series of excerpts from a byte stream (possibly out of order,
 * possibly overlapping) into an in-order byte stream.
 */
class StreamReassembler
{
private:
    priority_queue<ele, vector<ele>, greater<ele>> buffer;
    unordered_set<uint64_t> eleSet;
    size_t capacity;
    size_t ack;
    size_t eofAfterAck;
    // @desc: the reassembled in-order byte stream
    ByteStream _output;

public:
    /*
     * @desc: construct a `StreamReassembler` that will store up to `capacity` bytes.
     * @note: this capacity limits both the bytes that have been reassembled & those
     * that have not yet been reassembled.
     */
    StreamReassembler(const size_t capacity);

    /*
     * @desc: receives a substring and write any newly contiguous bytes into the stream.
     * @note: the StreamReassembler will stay within the memory limits of the `capacity`.
     * Bytes that would exceed the capacity are silently discarded.
     * @param data: the substring
     * @param index: indicates the index (place in sequence) of the first byte in `data`
     * @param eof: the last byte of `data` will be the last byte in the entire stream
     */
    void push_substring(const std::string &data, const uint64_t index, const bool eof);

    /*
     * @name: access the reassembled byte stream
     */
    const ByteStream &stream_out() const
    {
        return _output;
    }
    ByteStream &stream_out()
    {
        return _output;
    }
    /*@name ends*/

    /*
     * @desc: the number of bytes in the substrings stored but not yet reassembled.
     * @note: ff the byte at a particular index has been pushed more than once,
     * it should only be counted once for the purpose of this function.
     */
    size_t unassembled_bytes() const;

    /*
     * @desc: is the internal state empty (other than the output stream)?
     * @returns: `true` if no substrings are waiting to be assembled.
     */
    bool empty() const;

    /*
     * @desc: the acknowledge index of the stream, i.e., the index of the next interested substring.
     */
    size_t ack_index() const;
};

#endif // CRAPPY_STREAM_REASSEMBLER_HH_
