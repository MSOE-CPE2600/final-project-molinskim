# Bank Transaction System using POSIX Message Queues
## Overview
This program simulates a bank transaction system for inter-process communication

Multiple producers (users) to do transactions from separate terminals

Single consumer to process and track all transactions

Additionally prints a receipt to a text file that includes all transactions and a final balance.

## Features
Producers make transactions using d <amount> or w <amount> meaning deposit or withdrawal
The program also has a feature to gracefully exit by the producer using the 'q' command

## Files
producer.c => allows users to make transactions to the message queue
consumer.c => processes transactions, updates balance, and generates a receipt
Makefile => automates the build process
receipt.txt => contains a summary of all transactions and balance

## Running the Program
compile the programs using the Makefile => make clean => make
start a consumer and producer(s) in separate terminals using ./consumer and ./producer

## Example run
d 200
w 50
q

## Example output
Monitoring transactions...
Deposit: $200.00, New Balance: $200.00
Withdrawal: $50.00, New Balance: $150.00
Exit command received. Final balance: $150.00
Receipt printed to 'receipt.txt'.

'cat receipt.txt'

Transaction Receipt
-------------------
D $200.00, Balance: $200.00
W $50.00, Balance: $150.00
-------------------
Final Balance: $150.00
