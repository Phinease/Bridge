//
// Created by Phinease on 2019-02-11.
//

#ifndef BRIDGE_DATA_ANALYSE_PROCESS_H
#define BRIDGE_DATA_ANALYSE_PROCESS_H
#endif //BRIDGE_DATA_ANALYSE_PROCESS_H


#include "game.h"
#include <time.h>


int run[2]={1,0};
clock_t start_t, end_t;
double total_t;


void all();
void game_circle();
void analyse();


void all()
{
    start_t=clock();
    int i;
    for(i=0;i<run[1];i++,run[0]++){
        game_circle(0);
    }
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
}


void game_circle()
{
    int i,q,k;
    initialization();
    deal();
    //system("clear");
    process++;
    k=rand()%4;
    first_play_cards(k);
    for(i=1;i<4;i++) play_card((++k)%4);
    compare_cards();
    process++;
    for(i=0;i<11;i++){
        first_play_cards((0+winner)%4);
        play_card((1+winner)%4);
        play_card((2+winner)%4);
        play_card((3+winner)%4);
        compare_cards();
        process++;
    }
    if(print_func[0]==1) tricks();
    last_round();
    q=win(); // q==1 means NS win else WE win
    if(print_func[0]==1) congratulation(q);
    if(q==0){
        win_rate[0]++;
        printf("WE win\tWE [%d]  NS [%d]  Game times [%d]\n",win_rate[0],win_rate[1],run[0]);
    }else{
        win_rate[1]++;
        printf("NS win\tWE [%d]  NS [%d]  Game times [%d]\n",win_rate[0],win_rate[1],run[0]);
    }
}


void analyse()
{
    printf("Result: Games %d: %d times\t ",game,run[1]);
    printf("MC win rate: %.2f%%\t",100*(float)win_rate[0]/(float)(run[1]));
    printf("RD win rate: %.2f%%\n",100*(float)win_rate[1]/(float)(run[1]));
    printf("Simulation sampling WE %d times SN %d times.\n",simulation_times1,simulation_times2);
    end_t=clock();
    total_t=(double)(end_t-start_t)/CLOCKS_PER_SEC;
    printf("This spends %5.4f seconds, %4.5fs per game.\n",total_t,total_t/(float)run[1]);
}