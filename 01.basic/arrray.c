// #include <stdio.h>

// int average(int a[], int count)
// {
//     int sum = 0;
//     for (int i = 0; i < count; i++)
//     {
//         sum += a[i];
//     }
//     return sum / count;
// }
// int main(void)
// {
//     int temperature[5];
//     printf("Enter 5 temperatures: ");
//     for (int i = 0; i < 5; i++)
//     {
//         scanf_s("%d", &temperature[i]);
//     }
//     int result = average(temperature, 5);
//     printf("average=%d\n", result);
//     return 0;
// }
 #include <stdio.h>

 int find_max(int temperature[], int count)
 {
     int max = temperature[0];
     for (int i = 1; i < count; i++)
     {
         if (temperature[i] > max)
         {
             max = temperature[i];
         }
     }
     return max;
 }

    int main(void)
    {
        int temperature[5];
        printf("Enter 5 temperatures: ");
        for (int i = 0; i < 5; i++)
        {
            scanf_s("%d", &temperature[i]);
        }
        int result = find_max(temperature, 5);
        printf("max=%d\n", result);
        return 0;
    }