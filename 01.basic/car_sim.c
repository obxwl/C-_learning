#include <stdio.h>

int main(void)
{
    int speed = 0;
    int position = 0;

    for (int second = 1; second <= 5; second++)
    {
        speed += 2;
        position += speed;

        printf("second=%d speed=%d position=%d\n",
               second, speed, position);
    }

    return 0;
}

