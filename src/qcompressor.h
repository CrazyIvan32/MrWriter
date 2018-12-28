// this is from http://stackoverflow.com/a/24949005/1580081
// needs "LIBS += -lz" in .pro to link against zlib

#ifndef QCOMPRESSOR_H
#define QCOMPRESSOR_H

#include <zlib.h>
#include <QByteArray>

#define GZIP_WINDOWS_BIT 15 + 16
#define GZIP_CHUNK_SIZE 32 * 1024

/**
 * I got this from from http://stackoverflow.com/a/24949005/1580081
 *
 * For this to work, you need to add a line LIBS += -lz to your .pro file for linking against zlib.
 */
class QCompressor
{
public:
  static bool gzipCompress(QByteArray input, QByteArray &output, int level = -1);
  static bool gzipDecompress(QByteArray input, QByteArray &output);
};

#endif // QCOMPRESSOR_H
