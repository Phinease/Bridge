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
int mistake1=0,mistake2=0;


void all();
int game_circle(int signal);
int game_circle_backup(int signal);
void experiment(int signal);
void analyse();


void all()
{
    start_t=clock();
    int i,q,k;
    for(i=0;i<run[1];i++,run[0]++){
        experiment(0);
        q=game_circle(0);
        experiment(1);
        k=game_circle(1);
        if(q==k && q==1){
            mistake1++;
            experiment(0);
            q=game_circle_backup(0);
            experiment(1);
            k=game_circle_backup(1);
            if(q==k && q==1){
                printf("Error\n");
                mistake2++;
            }

        }
    }
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
}


void experiment(int signal)
{
    if(signal==0){
        player_random[0]=2;
        player_random[1]=1;
        player_random[2]=2;
        player_random[3]=1;
    }else
    {
        player_random[0]=1;
        player_random[1]=2;
        player_random[2]=1;
        player_random[3]=2;
    }
}


int game_circle(int signal)
{
    int i,q;
    initialization();
    deal(signal);
    //system("clear");
    process++;
    first_play_cards(0);
    for(i=1;i<4;i++) play_card(i);
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
    if(q==signal){
        win_rate[0]++;
        printf("Round %d MC win\tMC [%d]  RD [%d]  Game times [%d]\n",signal+1,win_rate[0],win_rate[1],run[0]*2);
        return 0;
    }else{
        win_rate[1]++;
        printf("Round %d RD win\tMC [%d]  RD [%d]  Game times [%d]\n",signal+1,win_rate[0],win_rate[1],run[0]*2);
        return 1;
    }
}


int game_circle_backup(int signal)
{
    int i,q;
    initialization();
    deal(1);
    //system("clear");
    process++;
    first_play_cards(0);
    for(i=1;i<4;i++) play_card(i);
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
    if(q==signal){
        printf("Verify %d MC win\n",signal+1);
        return 0;
    }else{
        printf("Verify %d RD win\n",signal+1);
        return 1;
    }
}


void analyse()
{
    printf("Result: Games %d: %d times\t ",game,run[1]*2);
    printf("MC win rate: %.2f%%\t",100*(float)win_rate[0]/(float)(run[1]*2));
    printf("RD win rate: %.2f%%\n",100*(float)win_rate[1]/(float)(run[1]*2));
    printf("Simulation sampling %d times.\t Mistakes first for %d second %d\n",simulation_times,mistake1,mistake2);
    end_t=clock();
    total_t=(double)(end_t-start_t)/CLOCKS_PER_SEC;
    printf("This spends %5.4f seconds, %4.5fs per game.\n",total_t,total_t/(float)run[1]);
}