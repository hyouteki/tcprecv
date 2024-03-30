#ifndef CRAPPY_BYTE_STREAM_HH_
#define CRAPPY_BYTE_STREAM_HH_

#include <deque>
#include <string>

#define EOF_CHAR 26

/*
 * @brief: an in-order byte stream.

 * @desc: bytes are written on the "input" side and read from the "output" side.
 * The byte stream is finite: the writer can end the input, and then no more
 * bytes can be written.
 */

class ByteStream
{
	std::deque<char> dq;
	size_t totalBytesWritten;
	size_t totalBytesPopped;
	int capacity;
	bool isInputEnded;

private:
	/*
	 * @desc: converts a character to a byte of its ascii value.
	 * @returns: array of bool of length 8; which is a byte.
	 */

	// @desc: flag indicating that the stream suffered an error.
	bool _error = false;

public:
	ByteStream(const size_t capacity);

	/*
	 * @name: `input` interface for the writer
	 */

	/*
	 * @desc: writes a string of bytes into the stream. Writes as many as will fit.
	 * @returns: the number of bytes accepted into the stream.
	 */
	size_t write(const std::string &data);

	// @returns: the number of additional bytes that the stream has space for.
	size_t remaining_capacity() const;

	// @desc: signal that the byte stream has reached its ending.
	void end_input();

	// @desc: indicate that the stream suffered an error.
	void set_error()
	{
		_error = true;
	}

	/*
	 * @name: `output` interface for the reader
	 */

	/*
	 * @desc: peek at next `len` bytes of the stream.
	 * @returns: a string.
	 */
	std::string peek_output(const size_t len);

	// @desc: remove bytes from the buffer.
	void pop_output(const size_t len);

	/*
	 * @desc: read (i.e., copy and then pop) the next "len" bytes of the stream.
	 * @returns: a string.
	 */
	std::string read(const size_t len);

	// @returns: `true` if the stream input has ended.
	bool input_ended() const;

	// @returns: `true` if the stream has suffered an error.
	bool error() const
	{
		return _error;
	}

	// @returns: `true` if buffer is full.
	bool isFull() const
	{
		return this->buffer_size() == this->capacity;
	}

	// @returns: the maximum amount that can currently be read from the stream.
	size_t buffer_size() const;

	// @returns: `true` if the buffer is empty.
	bool buffer_empty() const;

	// @returns: `true` if the output has reached the ending.
	bool eof() const;

	/*
	 * @name: `general` accounting
	 */

	// @desc: total number of bytes written.
	size_t bytes_written() const;

	// @desc: total number of bytes popped.
	size_t bytes_read() const;
};

#endif // CRAPPY_BYTE_STREAM_HH_
