#include <iostream>
#include <ctime>

using namespace std;

int main()
{
//    struct clock_t  *time0, *time1;
    double time0, time1, time;  
    time0 = clock();
     printf("time0=%g\n",time0);
    
    for(int j = 1; j <= 500; j++ )
 {   
        for(long int i = 1; i <= 10000; i++ )
        {
            int k;
            k = 1 + 1 - 1 - 1;     
        }
 }
    time1 = clock();
    printf("time1=%g\n",time1);
    printf("CLOCKS_PER_SEC=%g\n",CLOCKS_PER_SEC);//(*10^3)
    printf(" CLK_TCK=%g\n", CLK_TCK);
        
    cout << "°õ¦æ®É¶¡ : " 
         << (time1 - time0) / CLOCKS_PER_SEC
         << "¬í";
       time =  (double) difftime(time1, time0);
       printf("time=%g\n", time);
        
    
    system( "pause" );
    return 0;
}
