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
    printf("game?(1 for closed, 2 for open)\n");
    scanf("%d",&game);
    simulation_times=1000;
    run[1]=2000;
    print_func[0]=0;
    print_func[1]=0;
}