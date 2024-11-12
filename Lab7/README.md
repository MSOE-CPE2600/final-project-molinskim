# Vector Calculator 

## Description
A program that performs various calculations, 
including vector addition, subtraction, 
scalar multiplication, dot product, 
and cross product. It also supports loading 
and saving vectors from CSV files and 
dynamically allocates memory for vectors
as needed.

## Building the Program
To build the program, use the following commands:
make clean
make

## Running the Program
To run the program, use the following command:
./vcalc7

## Supported Commands
varname = x y z [Assigns a vector]
var1 + var2, var1 - var2 [Performs addition or subtraction]
var * scalar [Scalar multiplication]
dot(var1, var2) [Dot product]
cross(var1, var2) [Cross product]
load filename [Loads vectors from a file]
save filename [Saves vectors to a file]
list [Lists all vectors]
clear [Clears all vectors]
quit [Exits the program]