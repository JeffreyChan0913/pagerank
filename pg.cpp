#include <iostream>
#include <cmath>
#include <iomanip> 

//#define DEBUG
#define D2

int main(){
    
    double arr[5][5] = {
      {0, 0, 1, 0, 0},
      {1,0,0,0,0},
      {0,0.5,0,0,0},
      {0,0,0,0,0},
      {0,0.5,0,1,1}
    };
    double temp [5] = {0,0,0,0,0};
    double pi[5] = {1,1,1,1,1};
    bool converge[5] = {false, false, false, false, false};
    int time[5] = {0,0,0,0,0};
    double d = 0.85, dprime = 1-d, epsilon = 0.0001;
    int N = 5, convergeCounter = 0, iter = 0;
#ifdef DEBUG 
    std::cout << "Display all initial start up values" << std::endl;
    std::cout << "graph" << std::endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            std::cout << arr[i][j] << "\t ";
        }
        std::cout << "\n";
    }
    std::cout << "initial pi" << std::endl;
    for(auto x : pi)
        std::cout << x << " ";
    std::cout << "\n";
    std::cout << "Converge tracker" << std::endl;
    for(auto x : converge)
        std::cout << x << " ";
    std::cout << "\n";
    std::cout << "Basic constant" << std::endl;
    std::cout << "d: " << d << ", dprime: " << dprime << ", epsilon: " << epsilon << ", N: " << N << ", convergeCounter: " << 
      convergeCounter << std::endl;
    std::cout << "\n\n" << std::endl;
#endif
#ifdef D2
        std::cout << "*** means converged" << std::endl;
#endif
    /********************
     *****Core logic*****
     *******************/
    while(convergeCounter != 5){
        /**************************
         ***** Dot Product ********
         **************************/
        for(int row = 0; row < 5; row++){
            double dotProdValHolder = 0;
#ifdef DEBUG
            std::cout << "Node " << row  << ": " << std::endl;
#endif
            for(int col = 0; col < 5; col++){
#ifdef DEBUG
                std::cout << "Dot Product info" << std::endl;
                std::cout << "arr[" << row << "][" << col << "]: " << arr[row][col] << " x " << "pi[" << col << "] " << pi[col];
                std::cout << " = " << arr[row][col]* pi[col]<< std::endl;
#endif
                dotProdValHolder += (arr[row][col]* pi[col]); 
            }
            /*****************************
             ** Apply Page Rank Formula **
             *****************************/
            temp[row] = ((d*dotProdValHolder)+(dprime/N));
#ifdef DEBUG 
            std::cout << "new value for Pi: = " << temp[row] << std::endl;
#endif
        }
#ifdef DEBUG
        std::cout << "Done with dot product" << std::endl;
#endif
#ifdef D2
        std::cout << "Iteration: "<< iter << "\t";
        int count = 0;
        for(auto i : temp){
            if(converge[count] == true)
                std::cout << std::showpoint << std::setprecision(8) << " " << i << "***\t";
            else
                std::cout << std::showpoint << std::setprecision(8) << " " << i << "\t";
            if(count == 4)
                count = 0;
            else
                count += 1;
        }
        std::cout << std::endl;
#endif
        /*****************************
         **** Check for converges ****
         *****************************/
        int i = 0;
        while(i < 5){
            if(iter != 0){
                if(converge[i] == false){
                    if(abs(temp[i] - pi[i]) < epsilon){
#ifdef DEBUG
                        std::cout << "temp[i] = " << temp[i] << ", pi[i] = " << pi[i] << std::endl;
                        std::cout << "temp[i] -pi[i]: = " << abs(temp[i] - pi[i]) << std::endl;
#endif
                        time[i] = iter;
                        convergeCounter += 1;
                        converge[i] = true;
#ifdef DEBUG
                        std::cout << "Node " << i << " is converged" << std::endl;
#endif
                    }
                }
            }
            i += 1; 
        }
        for(int j = 0; j < 5; j++)
            pi[j] = temp[j];
        iter += 1;
#ifdef DEBUG
        std::cout << "Print new pi" << std::endl;
        for(auto i : pi)
            std::cout << i << "\t";
        std::cout<< std::endl;
        std::cout << "Done with printing new pi" << std::endl;
        std::cout << "\n\n" << std::endl;
#endif
    }

    /*************************
     ****** Output info ******
     *************************/

    std::cout << "Print info and statstics" << std::endl;
    for(auto x : pi)
        std::cout << x << "\t";
    std::cout << std::endl;
    std::cout << "Number of iteration: " << iter << std::endl;
    std::cout << "Number of iterations to converge" << std::endl;
    for(auto x : time)
        std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}
