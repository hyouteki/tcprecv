#include "stream_reassembler.hh"
#include <vector>
using std::cout;
using std::endl;

/*
hey you there can we take it to the next level baby do you dare - (Naked) by James Arthur.
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
0         1         2         3         4         5         6         7         8
*/

int main()
{
    StreamReassembler *stream_reassembler = new StreamReassembler(1500);
    std::vector<std::pair<int, std::string>> buffer = {
        {00, "hey you th"},
        {20, " take it t"},
        {40, " level bab"},
        {40, " level baby do "},
        {60, "are - (Nak"},
        {80, "es Arthur."},
        {10, "ere can we"},
        {30, "o the next"},
        {55, "you d"},
        {70, "ed) by Jam"},
    };
    for (auto sub_string : buffer)
        stream_reassembler->push_substring(sub_string.second, sub_string.first, false);
    std::string expected_result = "hey you there can we take it to the next level baby do you dare - (Naked) by James Arthur.";
    std::string reassembled_result = stream_reassembler->stream_out().read(90);
    cout << "expected_result   : " << expected_result << endl;
    cout << "reassembled_result: " << reassembled_result << endl;
    cout << "ack_index         : " << stream_reassembler->ack_index() << endl;
    cout << "is empty          : " << stream_reassembler->empty() << endl;
    cout << "unassembled bytes : " << stream_reassembler->unassembled_bytes() << endl;
    if (reassembled_result == expected_result)
        cout << "TEST SUCCEEDED" << endl;
    else
        cout << "TEST FAILED" << endl;
    return 0;
}