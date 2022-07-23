/**
 * Program to implement function to load data from text file.
 * Completion time: 30 minutes.
 * @author Mohammad Hamdan.
 * @version 1.0
 */




#include "DataLoader.h"



struct test_scenario* load_test_data(char* filename){


struct test_scenario* new_scenario =  malloc(sizeof(struct test_scenario));

FILE* file = fopen(filename, "r");

if (file == NULL){

  printf("no such file");
  return;
  }

  fscanf(file, "%d", &new_scenario->page_count);
  fscanf(file, "%d", &new_scenario->frame_count);
  fscanf(file, "%d", &new_scenario->refstr_len);

  for (int i=0; i< new_scenario->refstr_len; i++){

    fscanf(file, "%d",  &new_scenario->refstr[i]);
  }

return new_scenario;
}
