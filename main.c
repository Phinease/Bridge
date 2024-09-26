#include "process.h"
int random_start;

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
    printf("Start randomly? \n");
    scanf("%d",&random_start);
    run[1]=10000;
    simulation_times=0;
    player_random[0]=1;
    player_random[1]=1;
    player_random[2]=1;
    player_random[3]=1;
    print_func[0]=0;
    print_func[1]=0;
}