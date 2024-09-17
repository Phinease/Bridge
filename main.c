#include "process.h"


void debug_mode();


int main(){
    srand(time(NULL));
    debug_mode();
    all();
    analyse();
    return 0;
}

void debug_mode()
{
    game=1;
    printf("simulation_times?\n");
    scanf("%d",&simulation_times);
    run[1]=10000;
    player_random[0]=2;
    player_random[1]=1;
    player_random[2]=2;
    player_random[3]=1;
    print_func[0]=0;
    print_func[1]=0;
}