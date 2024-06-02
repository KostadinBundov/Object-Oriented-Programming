#include "StringViewer.h"

StringViewer::StringViewer(const char* start, const char* end) : start(start), end(end) { }

StringViewer::StringViewer(const char* str, size_t count) : StringViewer(str, str + count) { }

StringViewer::StringViewer(const char* str) : StringViewer(str, str + std::strlen(str)) { }

char StringViewer::operator[](size_t ind) const
{
    return start[ind];
}

size_t StringViewer::length() const
{
    return end - start;
}

bool StringViewer::isEmpty() const
{
    return length() == 0;
}

void StringViewer::removeSuffix(size_t count)
{
    if (count > length()) 
    {
        end = start;
    }
    else 
    {
        end -= count;
    }
}

void StringViewer::removePreffix(size_t count)
{
    if (count > length()) 
    {
        start = end;
    }
    else 
    {
        start += count;
    }
}