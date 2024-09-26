#include "process.h"


int debug_mode();


int main(){
    srand(2);
    if(debug_mode()==0) return -1;
    all();
    analyse();
    return 0;
}

int debug_mode()
{
    int wrong,answer;
    printf("Begin?(0 for yes, 1 for no)\n");
    scanf("%d",&answer);
    while(answer<0 || answer>1){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
        }
        printf("Wrong enter, retry.\n");
        scanf("%d",&answer);
    }
    if(answer==0){
        game=1;
        player_random[0]=2;
        player_random[1]=1;
        player_random[2]=2;
        player_random[3]=1;
        simulation_times=1000;
        run[1]=10000;
        print_func[0]=0;
        print_func[1]=0;
        return 1;
    } else{
        return 0;
    }
}