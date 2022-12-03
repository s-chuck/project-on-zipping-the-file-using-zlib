#include<iostream>
#include<zlib.h>
#include<fstream>
using namespace std;
int main() {
	ifstream fin("C:/Users/aswal/Desktop/coding answers/input.txt",ifstream::binary);
	if (!fin) return 0;

	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	int ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
	if (Z_OK != ret) {
		fin.close();
		return 0;
	}
	const int BUF = 1024;
	Bytef in[BUF];
	Bytef out[BUF];

	ofstream wp;
	wp.open("C:/Users/aswal/newone.txt",ofstream::binary);

	do {
		fin.read((char*)in, BUF);
		int readsize = fin.gcount();
		stream.avail_in = readsize;
		stream.next_in = in;
		int flush = Z_NO_FLUSH;
		if (fin.eof()) {
			flush = Z_FINISH;
		}
		do {
			stream.avail_out = BUF;
			stream.next_out = out;
			ret = deflate(&stream, flush);
			int dsize = BUF - stream.avail_out;
			wp.write((const char*)out, dsize);
		} while (0 != stream.avail_in);
	} while (Z_STREAM_END != ret);

	wp.close();
	deflateEnd(&stream);
	fin.close();
	return 0;
}