#include <stdio.h> 
#define OFFSET(s,f) ((char*)&(s.f)-(char*)&s)
typedef struct stockinfo
{
    int sell_indx; 
    int buy_indx; 
    float profit; 
} stockinfo_t; 

void Bursa(stockinfo_t *inf, float prices[], int size);

int main(void)
{
    /*float prices[] = {6, 12, 3, 5, 1, 4, 9, 2};*/ 
    stockinfo_t info = {0}; 
    /*Bursa(&info, prices, 8);*/ 
    printf("%d",OFFSET(info, buy_indx));
    /*printf("sell indx %d\nbuy indx %d\nprices %f\n",info.sell_indx, info.buy_indx, info.profit);*/ 
    return (0);
}

void Bursa(stockinfo_t *inf, float prices[], int size)
{

    float max_val = prices[0];
    float min_val = prices[0]; 
    int i = 0;
    
    for (i = 0; i < size; ++i)
    {
        if((max_val < prices[i])  || (inf-> buy_indx > inf->sell_indx))
        {
            max_val = prices[i];
            inf->sell_indx = i; 
        }
        
        if(min_val > prices[i]) 
        {
            min_val = prices[i];
            inf->buy_indx = i;
        }
    }
    
    inf-> profit = prices[inf-> sell_indx] - prices[inf-> buy_indx]; 
}

