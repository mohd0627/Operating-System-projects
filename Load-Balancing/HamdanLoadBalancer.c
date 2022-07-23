/**
* This file has the implementation of all the defined function
* in the LoadBalancer.h header file.
* @author Mohammad Hamdan.
* @version 1.0
*/




#include"InstanceHost.h"
#include"LoadBalancer.h"

struct balancer{

host* h;
job_node* jobList;
int k;
int counter;

pthread_mutex_t mutex;

};






balancer* balancer_create(int batch_size){

 balancer* new_balancer = (balancer*)malloc(sizeof(balancer));

 new_balancer->h = host_create();

 pthread_mutex_init(&(new_balancer->mutex), NULL);

 new_balancer->jobList=NULL;

 new_balancer->k = batch_size;
 new_balancer->counter = 0;

return new_balancer;
}


void balancer_destroy(balancer** lb){


 if ((*lb)->jobList == NULL) {
 job_node* iter = (*lb)->jobList;

 while(iter != NULL) {
       job_node* temp = iter->next;
        free(iter);
        iter = temp;
    }

 pthread_mutex_destroy(&((*lb)->mutex));
 free(*lb);
 *lb = NULL;



 }

 else {

    host_request_instance((*lb)->h, (*lb)->jobList);

 }

}



void balancer_add_job(balancer* lb, int user_id, int data, int* data_return){



if (lb->counter == lb->k){

printf("Load Balancer: Received new job from user #%d to process data=%d and store it at %p\n", user_id, data, data_return);

 host_request_instance(lb->h, lb->jobList);

 lb->counter = 0;

 job_node* iter = lb->jobList;

 while(iter != NULL) {
       job_node* temp = iter->next;
        free(iter);
        iter = temp;
    }


 job_node* new_node = (job_node*)malloc( sizeof(job_node));

 new_node->user_id = user_id;
 new_node->data = data;
 new_node->data_result = data_return;

 pthread_mutex_lock(&(lb->mutex));

 lb->jobList = new_node;

 lb->counter++;

 pthread_mutex_unlock(&(lb->mutex));
}


else {


 job_node* new_node = (job_node*)malloc(sizeof(job_node));

 new_node->user_id = user_id;
 new_node->data = data;
 new_node->data_result = data_return;

 pthread_mutex_lock(&(lb->mutex));

printf("Load Balancer: Received new job from user #%d to process data=%d and store it at %p\n", user_id, data, data_return);

 if (lb->jobList == NULL) {

    lb->jobList = new_node;
 }

 else {
 job_node* temp = lb->jobList;

 while (temp->next != NULL){

    temp = temp->next;
 }

 temp->next = new_node;

 lb->counter++;


 }
 pthread_mutex_unlock(&(lb->mutex));
 }

}
