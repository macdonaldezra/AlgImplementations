### Min Matrix Operations
Program determines the multiplication pairs required to minimize the amount of operations
required to multiply multiple matrices. The program can be verified by executing from the
command line - note that the first argument denotes the number of dimensions that will be
multiplied and the following arguments denote the dimensions required for the matrix
multiplications to take place. <br/>

### Example Run
Compile: `g++ matrix_op.cpp -o matrix_op` <br/>

Example Run:  `./matrix_op 5 2 2 3 4 4` <br/>
Example Output: `((X(XX))X) 56`