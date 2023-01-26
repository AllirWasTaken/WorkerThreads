#include "WorkerThreads.h"

#include <thread>


void WorkerThreads::WorkerFunction(){
    sem_wait(&semTask[0]);
    printf("OOOOOOOOH\n");

}

void WorkerThreads::SynchronizerFunction() {
    for(int i=0;i<currentlyPerformingTasks.size();i++){
        sem_post(&semTask[i]);
    }
}


WorkerThreads::WorkerThreads(unsigned workerCount) {
    CreateWorkers(workerCount);
    CreateThreadSynchronizer();

}

WorkerThreads::~WorkerThreads() {

}

void WorkerThreads::CreateWorkers(int64_t nt) {

    if(!nt)nt=std::thread::hardware_concurrency();

    currentlyPerformingTasks.resize(nt);
    threadWorkers=malloc(sizeof(HANDLE)*nt);
    semTask.resize(nt);


    for(int64_t i=0;i<nt;i++){
        currentlyPerformingTasks[i].handle=-1;
        currentlyPerformingTasks[i].priority=-1;
    }

    freeWorkers=nt;

    for(int64_t i=0;i<nt;i++){
        threadWorkers[i]=std::thread(&WorkerThreads::WorkerFunction);
    }




}