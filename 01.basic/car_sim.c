#include <stdio.h>
int limit(int speed, int limit ){
    if(speed > limit){
        speed = limit;
    }
    return speed;
}

int main(){
int speed = 0,position = 0 ,second = 0 ,target =0 ;
    scanf_s("%d",&target);
    if (target <=0)
    {
        printf("Invalid distance\n");
    }else{
while ( position < target)
        {
        second += 1;
        speed += 2 ;
        if( speed >=6){
            speed = limit(speed,6);
        }
        position += speed;
        printf("second=%d speed=%d position=%d\n", second, speed, position);    
        }
       return 0 ;
    }
}