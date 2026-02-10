#include "logger.h"
Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}
Logger::Logger()
{
    thread writeLogTask([&]()
    {
        for(;;)
        {
            time_t now = time(nullptr);
            tm* nowtm = localtime(&now);

            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt",nowtm->tm_year+1900, nowtm->tm_mon+1,nowtm->tm_mday);

            FILE* pf = fopen(file_name, "a+");
            if(pf == nullptr)
            {
                cout<< file_name<< "have no" << endl;
                exit(EXIT_FAILURE);
            }

            string msg = m_lckQue.Pop();

            char time_buf[128] = {0};
            sprintf(time_buf, "%d-%d-%d => [%s]",nowtm->tm_year+1900, nowtm->tm_mon+1,nowtm->tm_mday, (m_loglevel == INFO ? "info":"err"));
            msg.insert(0, time_buf);
            fputs(msg.c_str(), pf);
            fclose(pf);
        }
    });
    writeLogTask.detach();
}
void Logger::SetLogLevel(LogLevel level)
{
    m_loglevel - level;
}
void Logger::Log(string msg)
{
    m_lckQue.Push(msg);
}