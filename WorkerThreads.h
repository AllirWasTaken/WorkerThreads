#ifndef WORKER_THREADS_H
#define WORKER_THREADS_H


#include <vector>
#include <cstdint>
#include <semaphore>
#include <windows.h>



struct Task_WorkerThreads{
    void* func;
    void* funcArgs;
    void* funcResult;
    int64_t handle;
    int64_t priority;
};

struct Handle_WorkerThreads{
    int64_t Handle;
    Task_WorkerThreads *TaskPtr;
};

class WorkerThreads {
private:
    std::vector <Task_WorkerThreads> tasks;
    std::vector <Task_WorkerThreads> currentlyPerformingTasks;

    std::vector  <sem_t> semTask;
    sem_t semSynchronizer;

    int64_t freeWorkers;
    int64_t taskToDo;

    HANDLE threadWorkers;
    HANDLE threadSync;

    bool shutdown;

    void CreateWorkers(int64_t nt=0);
    void CreateThreadSynchronizer();
    void CreateThreadOverseer();
    void Defragmentation();
    void SortPriorities();




public:
    void WorkerFunction();

    void SynchronizerFunction();
    WorkerThreads(unsigned workerCount=0);
    ~WorkerThreads();
    int AddTask(int64_t *handle,void* func,void*args,int64_t priority=0);
    int GiveTaskPriority(int64_t handle);
    bool IsTaskOnList(int64_t handle);
    bool IsTaskBeingProcessed(int64_t handle);
    int NumberOfFreeWorkers();
    int NumberOfTasksToDo();
    void WaitForTaskToFinish();
    void Shutdown();
    bool SetPriority();
};


#endif
