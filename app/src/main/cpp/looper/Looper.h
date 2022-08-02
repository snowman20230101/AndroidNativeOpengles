//
// Created by windy on 2022/8/1.
//

#ifndef ANDROIDEXAMPLE_LOOPER_H
#define ANDROIDEXAMPLE_LOOPER_H

#include <cstdio>
#include <semaphore.h>

struct LooperMessage {
    int what;
    int arg1;
    int arg2;
    void *obj;
    LooperMessage *next;
    bool quit;
};

class Looper {

public:
    Looper();

    Looper &operator=(const Looper &) = delete;

    Looper(Looper &) = delete;

    virtual ~Looper();

    void postMessage(int what, bool flush = false);

    void postMessage(int what, void *obj, bool flush = false);

    void postMessage(int what, int arg1, int arg2, bool flush = false);

    void postMessage(int what, int arg1, int arg2, void *obj, bool flush = false);

    void quit();

    virtual void handleMessage(LooperMessage *msg);

private:
    void addMessage(LooperMessage *msg, bool flush);

    static void *trampoline(void *p);

    void loop(void);

    LooperMessage *head;
    pthread_t worker{};
    sem_t headWriteProtect{};
    sem_t headDataAvailable{};
    bool running;
};


#endif //ANDROIDEXAMPLE_LOOPER_H
