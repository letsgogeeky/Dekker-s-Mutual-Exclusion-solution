/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: ramy
 *
 * Created on January 28, 2018, 9:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const unsigned int ARRAY_SIZE = 10000;
int data_arr [10000];

int favouredthread = 1;

int thread1wantstoenter = 0;
int thread2wantstoenter = 0;

void* BubbleSortAsc(){

    long c, d, t;
    for(c = 0;c < (ARRAY_SIZE - 1); c++){
        for(d = 0;d < (ARRAY_SIZE - c - 1); d++){
            if(data_arr[d] > data_arr[d + 1]){
                //We're going to swap here.
                t = data_arr[d];
                data_arr[d] = data_arr[d + 1];
                data_arr[d + 1] = t;
            }
        }
    }
    printf("Exiting asccending sort\n");

}

void* BubbleSortDec(){


    long c, d, t;
    for(c = 0;c < (ARRAY_SIZE - 1); c++){
        for(d = 0;d < (ARRAY_SIZE - c - 1); d++){
            if(data_arr[d] < data_arr[d + 1]){
                //We're going to swap here.
                t = data_arr[d];
                data_arr[d] = data_arr[d + 1];
                data_arr[d + 1] = t;
            }
        }
    }
    printf("Exiting descending sort\n");

}

int IsSortedAsc(){
    int isSorted = 1; //True
    for(int c = 0; c < (ARRAY_SIZE); c++){
        if(data_arr[c] > data_arr[c + 1]){
             printf("Check sort Asc break at: %d\t",data_arr[c]);
            isSorted = 0;
            break;
        }
    }
    return isSorted;
}
int IsSortedDec(){
    int isSorted = 1; //True
    for(int c = 0; c < (ARRAY_SIZE); c++){
        if(data_arr[c] < data_arr[c + 1]){
            printf("Check sort Dec break at: %d\t",data_arr[c]);
            isSorted = 0;
            break;
        }
    }
    return isSorted;
}


void * Thread1(){

        thread1wantstoenter = 1;


        while(thread2wantstoenter == 1){
            if(favouredthread == 2){
                thread1wantstoenter = 0;

                while(favouredthread == 2);

                thread1wantstoenter = 1;
            }
        }
        BubbleSortAsc();

        favouredthread = 2;
        thread1wantstoenter = 0;
    return NULL;
}

void * Thread2(){
    
    thread2wantstoenter = 1;
    
    while(thread1wantstoenter == 1){
        if(favouredthread == 1){
            thread2wantstoenter = 0;
            
            while(favouredthread == 1);
            
            thread2wantstoenter = 1;
        }
    }
    BubbleSortDec();
    
    favouredthread = 1;
    
    thread2wantstoenter = 0;
    return NULL;
}
/*
 *
 */
int main(int argc, char** argv) {

      srand(time(NULL));
    for(int i = 0; i < 10000; i++){
        data_arr[i] =  rand() % 1000;

    }
         
 
     pthread_t t1, t2;

     pthread_create(&t1,NULL, Thread1,(void *)0);
     pthread_create(&t2,NULL, Thread2, (void *)1);


     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
     for(int i = 0; i < 100; i++){
        printf("%d\t",data_arr[i]);

    }
     int AscSort = IsSortedAsc();
     int DesSort = IsSortedDec();
     if (AscSort > 0){
         printf("Array is sorted assendingly\n");
     }
     if(DesSort > 0){
         printf("Array is sorted descendingly\n");
     }
     if(DesSort == 0 && AscSort == 0){
         printf("The array is not sorted at all!\n");
     }

    return (EXIT_SUCCESS);
}

