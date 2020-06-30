#include "logger.h"
#include <fstream> 
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif


namespace
{
const std::string filename = "save\\log.html";

#if defined(_WIN32)
bool fileExists(const std::string& filename)
{
    struct _stat buf;
    return _stat(filename.c_str(), &buf) != -1;
}

bool isDirExist(const std::string& path)
{
    struct _stat info;
    if (0 == _stat(path.c_str(), &info))
    {
        return (info.st_mode & _S_IFDIR) != 0;
    }
    return false;
}

bool createPath(const std::string& path)
{
    bool isCreated = 0 == _mkdir(path.c_str());
    if (!isCreated)
    {
        switch (errno)
        {
            case ENOENT: // parent didn't exist, try to create it
            {
                int pos = path.find_last_of('/');
                pos = (pos != std::string::npos) ? pos : path.find_last_of('\\');
                if (pos != std::string::npos)
                {
                    if (createPath(path.substr(0, pos)))
                    {
                        // now, try to create again
                        isCreated = 0 == _mkdir(path.c_str());
                    }
                }
            }
            break;

            case EEXIST: // done!
            {
                isCreated = isDirExist(path);
            }
            break;
        }
    }

    return isCreated;
}
#else
bool fileExists(const std::string& filename)
{
    struct stat buf;
    return stat(filename.c_str(), &buf) != -1;
}

bool isDirExist(const std::string& path)
{
    struct stat info;
    if (stat(path.c_str(), &info) == 0)
    {
        return (info.st_mode & _S_IFDIR) != 0;
    }
    return false;
}

bool createPath(const std::string& path)
{
    mode_t mode = 0755;
    bool isCreated = 0 == mkdir(path.c_str(), mode);
    if (!isCreated)
    {
        switch (errno)
        {
            case ENOENT: // parent didn't exist, try to create it
            {
                int pos = path.find_last_of('/');
                pos = (pos != std::string::npos) ? pos : path.find_last_of('\\');
                if (pos != std::string::npos)
                {
                    if (createPath(path.substr(0, pos)))
                    {
                        // now, try to create again
                        isCreated = 0 == mkdir(path.c_str(), mode);
                    }
                }
            }
            break;

            case EEXIST: // done!
            {
                isCreated = isDirExist(path);
            }
            break;
        }
    }

    return isCreated;
}
#endif
}

namespace stren
{
bool Logger::m_isFileExist = false;
std::streamoff Logger::m_writePos = 0;
std::fstream fs;

Logger::Logger(const char * colour)
    : m_printColour(colour)
{
    if (!m_isFileExist)
    {
        createPath("save");
        fs.open(filename.c_str(), std::fstream::out);
    }
    else
    {
        fs.open(filename.c_str(), std::fstream::in | std::fstream::out);
    }

    if (fs.good())
    {
        if (!m_isFileExist)
        {
            fs << "<html>\n\t<head>\n\t\t<title>Log</title>\n\t</head>\n";
            m_writePos = fs.tellg();
            m_isFileExist = true;
        }
        fs.seekg(m_writePos);
    }
    else
    {
        fs.close();
    }
}

Logger::Logger(const Logger & logger)
{
    m_printColour = logger.m_printColour;
}

Logger::Logger(Logger && logger)
{
    m_printColour = std::move(logger.m_printColour);
}

Logger & Logger::operator=(const Logger & logger)
{
    m_printColour = logger.m_printColour;
    return *this;
}

Logger & Logger::operator=(Logger && logger)
{
    m_printColour = std::move(logger.m_printColour);
    return *this;
}

Logger::~Logger()
{
    if (!m_isFileExist) return;
    if (!fs.is_open()) return;

    fs << "<br>\n";
    m_writePos = fs.tellg();
    fs << "</html>\0";
    fs.close();
}

void Logger::log(const char * data)
{
    if (!m_isFileExist) return;
    if (!fs.is_open()) return;

    fs.seekg(m_writePos);
    // TODO: optimize if needed - glue text together before puttin into stream
    fs << "\t<font color=\"" << m_printColour << "\">" << data << "</font>";
    m_writePos = fs.tellg();
}

void Logger::log(const std::string & data)
{
    log(data.c_str());
}

void Logger::log(const int data)
{
    if (!m_isFileExist) return;
    if (!fs.is_open()) return;

    fs.seekg(m_writePos);
    // TODO: optimize if needed - glue text together before puttin into stream
    fs << "\t<font color=\"" << m_printColour << "\">" << data << "</font>";
    m_writePos = fs.tellg();
}
} // stren