/**
 * Header file definition of functions to simulate a cloud-like server instance
 * host.
 *
 * @author Acuna
 * @version 1.1
 */

#ifndef INSTANCEHOST_H
#define INSTANCEHOST_H

#include "LoadBalancer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//struct for representing the host
typedef struct host host;

struct job_node; //defined in LoadBalancer

//forward declarations for (public) functions

/**
* Initializes the host environment.
*/
host* host_create();

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_destroy(host** h);

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host* h, struct job_node* batch);



/**
* Thread function to run a thread for every batch. The function takes
* a batch (a linked list of job_node), square the data in each node and
* return back to the user
*/


void* threadFunc(void* h);
#endif
