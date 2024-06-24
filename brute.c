#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define swap(x, y) {\
        uint8_t swap_tmp[sizeof(x) == sizeof(y) ? (int32_t)sizeof(x) : -1]; \
        memcpy(swap_tmp, &y, sizeof(x)); \
        memcpy(&y, &x, sizeof(x)); \
        memcpy(&x, swap_tmp, sizeof(x)); \
}


int main(void)
{
        double arr[] = {23, 23.93, 4.18, 8, 19, 4, 5, 19};
        int n = sizeof(arr)/sizeof(arr[0]);
        for(int i = 0; i < n; i++)
        {
                for(int j = i; j < n; j++)
                {
                        if(*(arr+i) < *(arr+j))
                        {
                                swap(*(arr+i), *(arr+j));
                        }
                }
        }

        for(int i = 0; i < n; i++)
        {
                printf("%f ", arr[i]);
        }
        return 0;
}
