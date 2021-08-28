/* Daniel Harper
 * CS2430
 * Recursion/Iteration Contrast 
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <math.h>

using namespace std;

/* Finds the Fibonacci result of a number (iNumber) using an recursive technique
 * Taken from Discrete Mathematics and it's Applications page 365 Alogrithm 7
 * 
 */
int fibonacciRecursive(int iNumber)
{
    if (iNumber == 0)
    {
	return 0;
    }
    else if (iNumber == 1)
    {
	return 1;
    }
    else
    {
	return fibonacciRecursive(iNumber - 1) + fibonacciRecursive(iNumber - 2);
    }
}

/* Finds the Fibonacci result of a number (iNumber) using an iterative technique
 * Taken from Discrete Mathematics and it's Applications page 366 Alogrithm 8
 * 
 */
int fibonacciIterative(int iNumber)
{
    if (iNumber == 0)
    {
	return 0;
    }
    else
    {
	int x = 0, y = 1;
	for (int i = 1; i <= iNumber - 1; i++)
	{
	    int z = x + y;
	    x = y;
	    y = z;
	}
	return y;
    }
}

/* Used to convert a number to another base.
 * Used a vector as the return type since the size of the result varies on the size of the number
 * Using algorithm 1 on page 249 of Discrete Mathmatics and It's Applications by Rosen
 */
vector<int> baseExpansion (int iNumToExpand, int iBase)
{
    vector<int> a;
    int iIterator = 0;
    int q = iNumToExpand;
    while (q != 0)
    {
	a.push_back(q % iBase);
	q /= iBase;
	iIterator++;
    }
    return a;
}


/* Finds the modular exponent of a number (iBase) raised to a power (iPower) mod iModulus
 * Using algorithm 5 on page 254 of Discrete Mathmatics and It's Applications by Rosen
 */
int findModularExponent(int iBase, int iPower, int iModulus)
{
    vector<int> vBinaryEquivOfPower;
    vBinaryEquivOfPower = baseExpansion(iPower, 2);
    int x = 1;
    int p = iBase % iModulus;
    for (int i = 0; i < vBinaryEquivOfPower.size(); i++)
    {
	if(vBinaryEquivOfPower[i] == 1)
	{
	    x = (x * p) % iModulus;
	        
	}
	p = (p * p) % iModulus;
    }
    return x;
}

/* Finds the modular exponent of a number (iBase) raised to a power (iPower) mod iModulus
 * Using algorithm 4 on page 363 of Discrete Mathmatics and It's Applications by Rosen
 */
int modularExponentiationRecursive(int iBase, int iPower, int iModulus)
{
    if (iPower == 0)
    {
	return 1;
    }
    else if ((iPower % 2) == 0)
    {
	int iTemp = modularExponentiationRecursive(iBase, iPower / 2, iModulus);
	return (iTemp * iTemp) % iModulus;
    }
    else
    {
	/* Order of operations messed me up on this part.  The book has it as 
	 * return (mpower(b, [n/2], m)^2 mod m * b mod m) mod m
	 * the m * b does not come before moding the m to the square of the previous result.
	 */
	int iTemp = modularExponentiationRecursive(iBase, iPower / 2, iModulus);
	return ((iTemp * iTemp) % iModulus * iBase) % iModulus;
    }
}


int main(int argc, char **argv) 
{
    timeval tStart, tFinish; //used to calculate the time a sort takes to run
    double dTime; //Used to calculate the difference between the times
    cout << fixed; //format the numbers that we put in cout to be a fixed length
    
    //**************Time the Recursive Fibonacci method***********************
    gettimeofday(&tStart, 0);
    fibonacciRecursive(40);
    gettimeofday(&tFinish, 0);
    /* The following is a variation of what was found here http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properl
     * Apparently the clock() and time() functions on linux are not the same as they are on Windows.  Linux returns seconds, Windows returns milliseconds;
     * And I spent an hour wondering why the documentation I was looking at didn't match up with what was happening */
    dTime = ((tFinish.tv_sec - tStart.tv_sec) * 1000 + (tFinish.tv_usec - tStart.tv_usec)/1000.0) + 0.5;
    dTime /= 1000;
    cout << "Recursive Fibonacci method took " << setprecision(10) << dTime << " seconds" << endl;
    
    //**************Time the Iterative Fibonacci method***********************
    gettimeofday(&tStart, 0);
    fibonacciIterative(40);
    gettimeofday(&tFinish, 0);
    /* The following is a variation of what was found here http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properl
     * Apparently the clock() and time() functions on linux are not the same as they are on Windows.  Linux returns seconds, Windows returns milliseconds;
     * And I spent an hour wondering why the documentation I was looking at didn't match up with what was happening */
    dTime = ((tFinish.tv_sec - tStart.tv_sec) * 1000 + (tFinish.tv_usec - tStart.tv_usec)/1000.0) + 0.5;
    dTime /= 1000;
    cout << "Iterative Fibonacci method took " << setprecision(10) << dTime << " seconds" << endl;

    //**************Time the Iterative Modular Exponent method***********************
    gettimeofday(&tStart, 0);
    cout << "The answer to 25 is : " << findModularExponent(7, 644, 645) << endl;
    cout << "The answer to 26 is : " << findModularExponent(11, 644, 645) << endl;
    cout << "The answer to 27 is : " << findModularExponent(3, 2003, 99) << endl;
    cout << "The answer to 28 is : " << findModularExponent(123, 1001, 101) << endl;
    gettimeofday(&tFinish, 0);
    /* The following is a variation of what was found here http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properl
     * Apparently the clock() and time() functions on linux are not the same as they are on Windows.  Linux returns seconds, Windows returns milliseconds;
     * And I spent an hour wondering why the documentation I was looking at didn't match up with what was happening */
    dTime = ((tFinish.tv_sec - tStart.tv_sec) * 1000 + (tFinish.tv_usec - tStart.tv_usec)/1000.0) + 0.5;
    dTime /= 1000;
    cout << "Iterative Modular Exponent method took " << setprecision(10) << dTime << " seconds" << endl;
    
    //**************Time the Recursive Modular Exponent method***********************
    gettimeofday(&tStart, 0);
    cout << "The answer to 25 is : " << modularExponentiationRecursive(7, 644, 645) << endl;
    cout << "The answer to 26 is : " << modularExponentiationRecursive(11, 644, 645) << endl;
    cout << "The answer to 27 is : " << modularExponentiationRecursive(3, 2003, 99) << endl;
    cout << "The answer to 28 is : " << modularExponentiationRecursive(123, 1001, 101) << endl;
    gettimeofday(&tFinish, 0);
    /* The following is a variation of what was found here http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properl
     * Apparently the clock() and time() functions on linux are not the same as they are on Windows.  Linux returns seconds, Windows returns milliseconds;
     * And I spent an hour wondering why the documentation I was looking at didn't match up with what was happening */
    dTime = ((tFinish.tv_sec - tStart.tv_sec) * 1000 + (tFinish.tv_usec - tStart.tv_usec)/1000.0) + 0.5;
    dTime /= 1000;
    cout << "Recursive Modular Exponent method took " << setprecision(10) << dTime << " seconds" << endl;
    
    cout << 6 % 11 << endl;
   

    return 0;
}
