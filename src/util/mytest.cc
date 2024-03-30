#include "byte_stream.cc"
#include <iostream>
using namespace std;

int main()
{
    ByteStream *byte_stream = new ByteStream(15);

    byte_stream->write("cat");

    cout << byte_stream->input_ended() << endl;
    cout << byte_stream->buffer_empty() << endl;
    cout << byte_stream->eof() << endl;
    cout << byte_stream->bytes_read() << endl;
    cout << byte_stream->bytes_written() << endl;
    cout << byte_stream->remaining_capacity() << endl;
    cout << byte_stream->buffer_size() << endl;
    cout << byte_stream->peek_output(3) << endl;

    byte_stream->end_input();

    cout << byte_stream->input_ended() << endl;
    cout << byte_stream->buffer_empty() << endl;
    cout << byte_stream->eof() << endl;
    cout << byte_stream->bytes_read() << endl;
    cout << byte_stream->bytes_written() << endl;
    cout << byte_stream->remaining_capacity() << endl;
    cout << byte_stream->buffer_size() << endl;
    cout << byte_stream->peek_output(3) << endl;

    byte_stream->pop_output(3);

    cout << byte_stream->input_ended() << endl;
    cout << byte_stream->buffer_empty() << endl;
    cout << byte_stream->eof() << endl;
    cout << byte_stream->bytes_read() << endl;
    cout << byte_stream->bytes_written() << endl;
    cout << byte_stream->remaining_capacity() << endl;
    cout << byte_stream->buffer_size() << endl;
    cout << byte_stream->peek_output(3) << endl;

    return 0;
}