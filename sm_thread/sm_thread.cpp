#include "sm_thread.h"

SmThread::SmThread():QThread()
{
     mt=new MovieTest();
}

void SmThread::run()
{
    mt->movie->start();
     int res=mt->exec();
        exec();
}
