#include "process.h"


void debug_mode();


int main(){
    srand(1);
    debug_mode();
    all();
    analyse();
    return 0;
}

void debug_mode()
{
    game=1;
    printf("How many games?\n");
    scanf("%d",&run[1]);
    simulation_times=0;
    player_random[0]=1;
    player_random[1]=1;
    player_random[2]=1;
    player_random[3]=1;
    print_func[0]=0;
    print_func[1]=0;
}