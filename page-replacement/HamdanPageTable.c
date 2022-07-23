/**
 * Program to implement functions and data structures for storing page tables, accessing it
 * and printing it.
 * Completion time: 3 hours.
 * @author Mohammad Hamdan.
 * @version 1.0
 */


#include"PageTable.h"


char *AlgorithmName[]={"FIFO", "LRU", "MFU"};

struct page_table_entry{

int page_number;
int frame_number;
unsigned int valid;
unsigned int dirty;
int counter;
int order;

};

struct page_table{

struct page_table_entry* table;
enum replacement_algorithm algorithm;
int verbose;
int size;
int page_fault;
int frames;
int frames_counter;
int order;
};


struct page_table* page_table_create(int page_count, int frame_count, enum replacement_algorithm algorithm, int verbose){

struct page_table* new_table = malloc(sizeof(struct page_table));
new_table->algorithm = algorithm;
new_table->verbose= verbose;
new_table->size=page_count;
new_table->page_fault=0;
new_table->frames = frame_count;
new_table->frames_counter=0;
new_table->order=0;

new_table->table = malloc(sizeof(struct page_table_entry)*4);

for (int i=0; i<page_count; i++){

    new_table->table[i].valid=0;
    new_table->table[i].dirty=0;
    new_table->table[i].page_number=i;
    new_table->table[i].frame_number=-1;
    new_table->table[i].counter=0;

}

return new_table;
}


void page_table_destroy(struct page_table** pt){

free(*pt);
*pt=NULL;

}




void page_table_access_page(struct page_table *pt, int page){

if (pt->algorithm == FIFO){

 if (pt->table[page].valid==0){

    if (pt->table[page].frame_number < 0){

            if (pt->frames_counter < pt->frames){

      pt->table[page].frame_number = pt->frames_counter;
      pt->table[page].valid=1;
      pt->table[page].counter++;
      pt->frames_counter++;
      pt->order++;
      pt->table[page].order = pt->order;
      pt->page_fault++;

            }

            else {

                 int temp=pt->table[0].order;
                 int temp2=0;

               for (int i=0; i<pt->size; i++){

                    if (i != page){

                   if (temp > pt->table[i].order){

                    temp = pt->table[i].order;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                    }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;


            }
    }

     else if (pt->table[page].frame_number != -1){

                int temp=pt->table[0].order;
                int temp2=0;

               for (int i=0; i<pt->size; i++){

                   if (i != page){
                   if (temp > pt->table[i].order){

                    temp = pt->table[i].order;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                   }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;



     }
     return;
 }

 else if (pt->table[page].valid == 1){

    pt->table[page].counter++;

 }

}





else if (pt->algorithm == LRU){

if (pt->table[page].valid==0){

    if (pt->table[page].frame_number < 0){

            if (pt->frames_counter < pt->frames){

      pt->table[page].frame_number = pt->frames_counter;
      pt->table[page].valid=1;
      pt->table[page].counter++;
      pt->frames_counter++;
      pt->order++;
      pt->table[page].order = pt->order;
      pt->page_fault++;

            }

            else {

                 int temp=pt->table[0].counter;
                 int temp2=0;

               for (int i=0; i < pt->size; i++){

                 if (i != page){
                   if (temp > pt->table[i].counter){

                    temp = pt->table[i].counter;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                 }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;


            }
    }

     else if (pt->table[page].frame_number != -1){

                int temp=pt->table[0].counter;
                int temp2=0;

               for (int i=0; i<pt->size; i++){

                 if (i != page){
                   if (temp > pt->table[i].counter){

                    temp = pt->table[i].counter;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                 }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;



     }
     return;
 }

 else if (pt->table[page].valid == 1){

    pt->table[page].counter++;
    pt->order++;
    pt->table[page].order = pt->order;

 }
}


else if (pt->algorithm == MFU){


if (pt->table[page].valid==0){

    if (pt->table[page].frame_number < 0){

            if (pt->frames_counter < pt->frames){

      pt->table[page].frame_number = pt->frames_counter;
      pt->table[page].valid=1;
      pt->table[page].counter++;
      pt->frames_counter++;
      pt->order++;
      pt->table[page].order = pt->order;
      pt->page_fault++;

            }

            else {

                 int temp=pt->table[0].counter;
                 int temp2=0;

               for (int i=0; i<pt->size; i++){

                 if (i != page){
                   if (temp > pt->table[i].counter){

                    temp = pt->table[i].counter;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                 }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;


            }
    }

     else if (pt->table[page].frame_number != -1){

                int temp=pt->table[0].counter;
                int temp2=0;

               for (int i=0; i<pt->size; i++){

                    if (i != page){

                   if (temp < pt->table[i].counter){

                    temp = pt->table[i].counter;
                    temp2 = pt->table[i].frame_number;
                    pt->table[i].valid=0;
                   }
                    }

               }
               pt->table[page].frame_number = temp2;
               pt->table[page].counter++;
               pt->table[page].valid=1;
               pt->order++;
               pt->table[page].order = pt->order;
               pt->page_fault++;



     }
     return;
 }

 else if (pt->table[page].valid == 1){

    pt->table[page].counter++;
    pt->order++;
    pt->table[page].order = pt->order;

 }

}


}


void page_table_display(struct page_table* pt){

printf("==== Page Table ====\n");
printf("Mode : %s\n", AlgorithmName[pt->algorithm]);
printf("Page Faults : %d\n", pt->page_fault);

page_table_display_contents(pt);

}

void page_table_display_contents(struct page_table *pt){

if (pt->verbose==1){
printf("page frame | dirty valid | order  last freq\n");

for (int i=0; i<pt->size; i++){

    printf("%d %d | %d %d | %d  %d %d\n",i, pt->table[i].frame_number, pt->table[i].dirty, pt->table[i].valid,
    pt->table[i].order, pt->table[i].order, pt->table[i].counter);

}
}

else if (pt->verbose==0){

    printf("page frame | dirty valid\n");

for (int i=0; i<pt->size; i++){

    printf("%d     %d |     %d     %d\n",i, pt->table[i].frame_number, pt->table[i].dirty, pt->table[i].valid);

}

}

}


