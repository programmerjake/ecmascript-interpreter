#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

#include <cwchar>
#include <string>
#include <iosfwd>

template <typename ToType>
struct string_cast;

template <typename T>
class string_cast<std::basic_string<T>>
{
    std::basic_string<T> str;
public:
    string_cast(std::basic_string<T> inputString)
        : str(inputString)
    {
    }
    operator std::basic_string<T>() const
    {
        return str;
    }
};

class utf8_format_error : public std::runtime_error
{
public:
    utf8_format_error(std::string msg)
        : runtime_error(msg)
    {
    }
};

class utf16_format_error : public std::runtime_error
{
public:
    utf16_format_error(std::string msg)
        : runtime_error(msg)
    {
    }
};

template <>
class string_cast<std::basic_string<wchar_t>>
{
    std::basic_string<wchar_t> retval;
public:
    string_cast(std::basic_string<wchar_t> inputString)
        : retval(inputString)
    {
    }
    string_cast(std::basic_string<char> inputString)
    {
        retval.reserve(inputString.size());
        for(size_t i = 0; i < inputString.size(); i++)
        {
            unsigned char ch = (unsigned char)inputString[i];
            if((ch & 0x80) == 0) // one byte sequence
            {
                retval += (wchar_t)ch;
            }
            else if((ch & 0xE0) == 0xC0) // two byte sequence
            {
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("2 byte sequence missing last byte");
                unsigned char ch2 = (unsigned char)inputString[i];
                if((ch2 & 0xC0) != 0x80)
                    throw utf8_format_error("last byte in 2 byte sequence is not a continuation byte");
                unsigned value = ch & 0x1F;
                value <<= 6;
                value |= ch2 & 0x3F;
                retval += (wchar_t)value;
            }
            else if((ch & 0xF0) == 0xE0) // three byte sequence
            {
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("3 byte sequence missing second byte");
                unsigned char ch2 = (unsigned char)inputString[i];
                if((ch2 & 0xC0) != 0x80)
                    throw utf8_format_error("second byte in 3 byte sequence is not a continuation byte");
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("3 byte sequence missing last byte");
                unsigned char ch3 = (unsigned char)inputString[i];
                if((ch3 & 0xC0) != 0x80)
                    throw utf8_format_error("last byte in 3 byte sequence is not a continuation byte");
                unsigned value = ch & 0xF;
                value <<= 6;
                value |= ch2 & 0x3F;
                value <<= 6;
                value |= ch3 & 0x3F;
                retval += (wchar_t)value;
            }
            else if((ch & 0xF8) == 0xF0) // four byte sequence
            {
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("4 byte sequence missing second byte");
                unsigned char ch2 = (unsigned char)inputString[i];
                if((ch2 & 0xC0) != 0x80)
                    throw utf8_format_error("second byte in 4 byte sequence is not a continuation byte");
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("4 byte sequence missing third byte");
                unsigned char ch3 = (unsigned char)inputString[i];
                if((ch3 & 0xC0) != 0x80)
                    throw utf8_format_error("third byte in 4 byte sequence is not a continuation byte");
                i++;
                if(i >= inputString.size())
                    throw utf8_format_error("4 byte sequence missing last byte");
                unsigned char ch4 = (unsigned char)inputString[i];
                if((ch4 & 0xC0) != 0x80)
                    throw utf8_format_error("last byte in 4 byte sequence is not a continuation byte");
                unsigned value = ch & 0x7;
                value <<= 6;
                value |= ch2 & 0x3F;
                value <<= 6;
                value |= ch3 & 0x3F;
                value <<= 6;
                value |= ch4 & 0x3F;
                if(value > 0x10FFFF)
                    throw utf8_format_error("unicode code point out of range");
#if WCHAR_MAX - WCHAR_MIN >= 0x10000 // wchar_t is 32 bits
                retval += (wchar_t)value;
#else // wchar_t is 16 bits
                if(value > 0xFFFF)
                {
                    unsigned highValue = ((value >> 10) & 0x3FF) + 0xD800;
                    unsigned lowValue = (value & 0x3FF) + 0xDC00;
                    retval += (wchar_t)highValue;
                    retval += (wchar_t)lowValue;
                }
                else
                    retval += (wchar_t)value;
#endif
            }
            else if((ch & 0xC0) == 0x80)
                throw utf8_format_error("unexpected continuation byte");
            else
                throw utf8_format_error("invalid byte");
        }
    }
    operator std::basic_string<wchar_t>() const
    {
        return retval;
    }
};

template <>
class string_cast<std::basic_string<char>>
{
    std::basic_string<char> retval;
public:
    string_cast(std::basic_string<char> inputString)
        : retval(inputString)
    {
    }
    string_cast(std::basic_string<wchar_t> inputString)
    {
        retval.reserve(inputString.size());
        for(size_t i = 0; i < inputString.size(); i++)
        {
            wchar_t ch = inputString[i];
#if WCHAR_MAX - WCHAR_MIN >= 0x10000 // wchar_t is 32 bits
            unsigned value = (unsigned)ch;
#else // wchar_t is 16 bits
            unsigned value = (unsigned)ch & 0xFFFF;
            if(value >= 0xD800 && value <= 0xDBFF) // surrogate high word
            {
                if(i + 1 < inputString.size())
                {
                    unsigned value2 = (unsigned)inputString[i + 1] & 0xFFFF;
                    if(value2 >= 0xDC00 && value2 <= 0xDFFF)
                    {
                        i++;
                        value &= 0x3FF;
                        value <<= 10;
                        value |= value2 & 0x3FF;
                    }
                }
            }
#endif
            if(value < 0x80)
            {
                retval += (char)value;
            }
            else if(value < 0x800)
            {
                retval += (char)((value >> 6) | 0xC0);
                retval += (char)((value & 0x3F) | 0x80);
            }
            else if(value < 0x10000)
            {
                retval += (char)((value >> 12) | 0xE0);
                retval += (char)(((value >> 6) & 0x3F) | 0x80);
                retval += (char)((value & 0x3F) | 0x80);
            }
            else if(value <= 0x10FFFF)
            {
                retval += (char)((value >> 18) | 0xF0);
                retval += (char)(((value >> 12) & 0x3F) | 0x80);
                retval += (char)(((value >> 6) & 0x3F) | 0x80);
                retval += (char)((value & 0x3F) | 0x80);
            }
            else
                throw utf16_format_error("unicode code point out of range");
        }
    }
    operator std::basic_string<char>() const
    {
        return retval;
    }
};

template <typename T>
inline std::basic_ostream<T> & operator <<(std::basic_ostream<T> & os, const string_cast<std::basic_string<T>> & str)
{
    return os << (std::basic_string<T>)str;
}

#endif // CONVERT_H_INCLUDED
