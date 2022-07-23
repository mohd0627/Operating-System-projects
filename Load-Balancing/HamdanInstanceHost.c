/**
* This file has the implementation of all the defined function
* in the InstanceHost.h header file.
* @author Mohammad Hamdan.
* @version 1.0
*/


#include "InstanceHost.h"
#include "LoadBalancer.h"

struct host{

job_node* activeJobsList;
pthread_mutex_t mutex;

};



host* host_create(){

host* new_host = (host*)malloc(sizeof(host));

new_host->activeJobsList = NULL;

pthread_mutex_init(&(new_host->mutex), NULL);

return new_host;

}


void host_destroy(host** h){

if ((*h)->activeJobsList == NULL) {

 job_node* iter = (*h)->activeJobsList;

 while(iter != NULL) {

       job_node* temp = iter->next;
        free(iter);
        iter = temp;
    }

 pthread_mutex_destroy(&((*h)->mutex));
 free(*h);
 *h = NULL;


 }


 else {

    host_request_instance(*h, (*h)->activeJobsList);

 }

}



void host_request_instance(host* h, job_node* batch){


 printf("Load Balancer: Received batch and spinning up new instance\n");

 h->activeJobsList = batch;


 pthread_t thread;

 pthread_create(&thread, NULL, &threadFunc, (void*)h);

 pthread_join(thread, NULL);

}





void* threadFunc(void* h){

 host* h1 = (host*) h;

 pthread_mutex_lock(&(h1->mutex));


 while (h1->activeJobsList != NULL){

    int x = (h1->activeJobsList->data)*(h1->activeJobsList->data);
    h1->activeJobsList->data_result = &x;
    h1->activeJobsList = h1->activeJobsList->next;
}

job_node* iter = h1->activeJobsList;

 while(iter != NULL) {

       job_node* temp = iter->next;
        free(iter);
        iter = temp;
    }


 pthread_mutex_unlock(&(h1->mutex));

}
