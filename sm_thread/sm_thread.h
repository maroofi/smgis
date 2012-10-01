#ifndef SM_THREAD_H
#define SM_THREAD_H
#include <QThread>
#include "../movie_test/movie_test.h"
class SmThread : public QThread
{
public:
    SmThread();
    MovieTest* mt;
protected:
    void run();
};

#endif // SM_THREAD_H
