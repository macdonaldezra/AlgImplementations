# FFT Implementations

This project consists of Fast Fourier Transform implementations as they are applied
to polynomial multiplication. The included implementations include one implemented
recursively and the other iteratively, using butterfly operations. The implemented 
algorithms in fft.c are implemented directly from Chapter 30 of MIT's Introduction 
to Algorithms textbook on Fast Fourier Transform.

### Installation
The project includes a makefile that creates two executibles, one for generating test
polynomials to multiply, and the other to compute their product using an FFT.

##### Name: polyGenerator                                                    
                                                                
###### Usage:
    ./polyGenerator <max_coefficients> <max_coefficient_value>     
                                                                
##### Description:                                                           
Creates a file in ./resource folder that includes two sets of polynomial coefficients whose lengths are specified on the first line of the output file. The next two lines contain the coefficients of each respective polynomial.
                                                                             
##### Name: polyProduct                                                         
                                                                          
###### Usage:
    ./polyProduct <input_file>                                       
                                                                          
##### Description:                                                              
Creates a file in ./resource folder that includes two sets of integer polynomial coefficients whose lengths are specified on the first line of the output file. The next two lines contain the coefficients of each respective polynomial. Polynomial multiplication is done by using the following general algorithm, given two polynomials A(x) and B(x): 

&nbsp;&nbsp;&nbsp;1. Compute DFT of A(x) and B(x)                                     
&nbsp;&nbsp;&nbsp;2. Compute C(x) = A(x) * B(x)                                       
&nbsp;&nbsp;&nbsp;3. Compute Inverse DFT on C(x) and return resulting coefficients    
