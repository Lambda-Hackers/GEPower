#ifndef _COMMON_LOGOUT_H_
#define _COMMON_LOGOUT_H_
#include<string>
#include<fstream>
#include<iostream>

#define log *getStream()
class Stream
{
public:
    template<typename T>
    std::ostream &operator<<(T t){
        m_outStream << t;
        m_outStream.flush();
        std::cout << "1111" << std::endl;
        return m_outStream;
    }

    Stream(std::string& path)
    {
        m_outStream.open(path, std::ostream::app);
    }

    ~Stream()
    {
        m_outStream.close();
    }
private:
    std::fstream m_outStream;
};

namespace logOut
{
    bool openStream(std::string path);

    // try to close log, no error(if something error just ignored)
    void closeStream();

    //
    Stream* getStream();

};

using namespace logOut;
#endif