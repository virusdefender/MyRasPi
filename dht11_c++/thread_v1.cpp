#include <iostream>
#include <pthread.h> //多线程相关操作头文件，可移植众多平台

using namespace std;

#define NUM_THREADS 5 //线程数

void* say_hello( void* args )
{
    cout << "hello in thread " << *( (int *)args ) <<  endl;
} //函数返回的是函数指针，便于后面作为参数

int main()
{
    pthread_t tids[NUM_THREADS]; //线程id
    int indexes[NUM_THREADS]; //用来保存i的值避免被修改

    for( int i = 0; i < NUM_THREADS; ++i )
    {
        indexes[i] = i;
        int ret = pthread_create( &tids[i], NULL, say_hello, (void*)&(indexes[i]) );
        if( ret != 0 ) //创建线程成功返回0
        {
            cout << "pthread_create error:error_code=" << ret << endl;
        }
    }
    for( int i = 0; i < NUM_THREADS; ++i )
        pthread_join( tids[i], NULL ); //pthread_join用来等待一个线程的结束，是一个线程阻塞的函数
}

