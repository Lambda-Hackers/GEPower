#include"logout.h"

#define LINEBREAK "\n"

LogStream* logOut::openStream(const char* path)
{
    return new LogStream(path);
}

void logOut::closeStream(LogStream* logStream)
{
    delete logStream;
}

void logOut::outf(LogStream* stream, LOG_OUT_CLASS outClass, const char* context)
{
    stream->outf(outClass, context);
    stream->outf(outClass, LINEBREAK);
}

void logOut::outv(LogStream* stream, LOG_OUT_CLASS outClass, const char *format, ...)
{
    if (format == NULL || *format == 0)
		return;

    if (stream == NULL)
    {
        outToStderr("out stream have not been initial\n");
        return;
    }

	va_list ap;
	va_start(ap, format);

    stream->outf(outClass, format, ap);
    stream->outf(outClass, LINEBREAK);

	va_end(ap);
}