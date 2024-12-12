/**********************************************************
* Name: Marshall Molinski
* Course: CPE-2600 Systems Programming
* Assignment: Lab 13 - Final Project
* Date: 12/9/2024
* Description: C program that handles multiple bank account
*              transactions accurately from multiple sources
* Compile Instructions: make clean => make => ./producer => 
                        new terminal => ./consumer
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/transaction_queue"
#define MAX_SIZE 1024
#define MAX_LOG 100 //max number of transactions to log

//struct to store transaction details
typedef struct {
    char type;
    double amount;
    double balance;
} TransactionLog;

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];
    double balance = 0.0;
    TransactionLog log[MAX_LOG]; //array to store transactions
    int log_count = 0; //counter for transactions

    //open the message queue (O_RDONLY: read only access)
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Monitoring transactions...\n");

    while (1) {
        //receive a transaction message
        if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        //check for exit command
        if (strcmp(buffer, "q") == 0) {
            printf("Exit command received. Final balance: $%.2f\n", balance);
            
            //print receipt to a file
            FILE* receipt = fopen("receipt.txt", "w");
            if (!receipt) {
                perror("Failed to create receipt file");
                exit(EXIT_FAILURE);
            }
            fprintf(receipt, "Transaction Receipt\n");
            fprintf(receipt, "-------------------\n");
            for (int i = 0; i < log_count; i++) {
                 fprintf(receipt, "%c $%.2f, Balance : $%.2f\n", log[i].type, log[i].amount,log[i].balance);
            }
            fprintf(receipt, "------------------\n");
            fprintf(receipt, "Final Balance: $%.2f\n", balance);
            fclose(receipt);

            fprintf(receipt, "Receipt printed to 'receipt.txt'.\n");
            break;
        }

        //parse the transaction
        char type;
        double amount;
        if (sscanf(buffer, "%c %lf", &type, &amount) != 2) {
            printf("Invalid transaction format: %s\n", buffer);
            continue;
        }

        //process the transaction
        if (type == 'd') {
            balance += amount;
            printf("Deposit: $%.2f, New Balance: $%.2f\n", amount, balance);
        } else if (type == 'w') {
            if (balance >= amount) {
                balance -= amount;
                printf("Withdrawal: $%.2f, New Balance: $%.2f\n", amount, balance);
            } else {
                printf("Withdrawal: $%.2f declined, Insufficient Funds\n", amount);
            }
        } else {
            printf("Unknown transaction type: %s\n", buffer);
            continue;
        }

        //log the transaction
        if (log_count < MAX_LOG){
            log[log_count].type = type;
            log[log_count].amount = amount;
            log[log_count].balance = balance;
            log_count++;
        } else {
            printf("Transaction log is full. Cannot log more transactions.\n");
        }

    }

    //cleanup
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }
    return 0;
}