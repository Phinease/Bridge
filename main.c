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
    printf("Simulation times WE\n");
    scanf("%d",&simulation_times1);
    printf("Simulation times NS\n");
    scanf("%d",&simulation_times2);
    run[1]=20000;
    player_random[0]=2;
    player_random[1]=2;
    player_random[2]=2;
    player_random[3]=2;
    print_func[0]=0;
    print_func[1]=0;
}