/**********************************************************
* Name: Marshall Molinski
* Course: CPE-2600 Systems Programming
* Assignment: Lab 13 - Final Project
* Date: 12/9/2024
* Description: C program that handles multiple bank account
*              transactions accurately from multiple sources
* Compile Instructions: make clean => make => ./bank_sim
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/transaction_queue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    //initialize the queue attributes
    attr.mq_flags = 0;            //blocking mode (wait)
    attr.mq_maxmsg = 10;          //maximum messages in the queue
    attr.mq_msgsize = MAX_SIZE;   //maximum size of each message
    attr.mq_curmsgs = 0;          //number of messages currently in queue

    //create the message queue (O_WRONLY: write only access)
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Enter transactions (e.g., 'd 100' for deposit $100 or 's 50 for withdrawal $50'): \n");
    printf("Enter 'q' to quit.\n");
    while (1) {
        printf("Transaction: ");
        fgets(buffer, MAX_SIZE, stdin);

        //remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        //check for exit command
        if (strcmp(buffer, "q") == 0) {
            //send the exit message
            if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Exit message sent. Have a great day!\n");
            break;
        }

        //send the transaction message
        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
        printf("Transaction sent: %s\n", buffer);
    }

    //cleanup
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    return 0;
}