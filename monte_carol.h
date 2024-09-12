//
// Created by Phinease on 2019-02-11.
//

#ifndef BRIDGE_DATA_ANALYSE_MONTE_CAROL_H
#define BRIDGE_DATA_ANALYSE_MONTE_CAROL_H

#endif //BRIDGE_DATA_ANALYSE_MONTE_CAROL_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/*
 * Rule basic: card_num based on a base 4
 * C/D/H/S(/N) -> 0/1/2/3(/4)
 * "2/3/4/5/6/7/8/9/T/J/Q/K/A" -> 0/1/2/3/4/5/6/7/8/9/10/11/12
 * num_user:
 * 'W','N','E','S' -> "West","North","East","South" -> 0/1/2/3
 * -1 for all kinds is non-existence.
 */

//clock_t start_simulate, end_simulate;
//time_counting variables


char *Users_name[4]={"Player West","Player North","Player East","Player South"};
char *Suits_fullname[5]={"Club","Diamond","Heart","Spade","none"};
char Height[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
char Suits_name[4]={'C','D','H','S'};
char U_N[4]={'W','N','E','S'};


struct simulate{
    int suit;
    int flag;
    int c_played[4];
    int num_user;
};


struct simulate original,test;
struct simulate *p_orig=&original, *p_test=&test;


extern int Users_Nums[4][13],local_suit,Cards_played[4];
extern int User_Unknown[4][39];
extern int process,game;
extern int print_func[2];


int c_num_open[13];
int c_num_close[39];


int simulation(int times,int num_user);
int random_player(int *p,int flag);
int c_open();
int c_close();
int cc(int num_user);
int min_card();
int rp_open(int flag);
int rp_close(int flag);



int random_player (int *p,int flag){ //random num_user for the game
    int *p2=p;
    int nb_card=0,local_card=0;
    int i,result;
    if(flag==1){ // flag - 1 means first to play
        for(i=0;i<13;i++){
            if(*p++==-1) break;
            nb_card++;
        }
        result=(rand()%nb_card);
        //printf("1.%d\n",nb_card);
        return result;
    }
    else {
        for(i=0;i<13;i++){
            if(*p++%4==local_suit){
                local_card++;
            }
        }
        nb_card=0;
        for(i=0;i<13;i++){
            if(*p2++%4<local_suit){
                nb_card++;
            }else{
                break;
            }
        }
        if(local_card==0){
            result=rand()%(13-process);
        }else{
            result=nb_card+(rand()%local_card);
        }
        //printf("\n2.%d %d\n",nb_card,local_card);
        return result;
    }
}


int rp_open(int flag)
{
    int nb_card=0,local_card=0;
    int i,result;
    nb_card=c_open();
    //printf("NOW random open. flag: %d\n",flag);
    if(flag==1){ // flag 1 means first to play
        result=rand()%nb_card;
        //printf("Nb_card.%d\n",nb_card);
        test.suit=c_num_open[result]%4;
        test.c_played[test.num_user]=c_num_open[result];
        return result;
    }
    else {
        for(i=0;i<13;i++){
            if(c_num_open[i]%4==test.suit){
                local_card++;
            }
        }
        //printf("local_card: %d\n",local_card);
        nb_card=0;
        for(i=0;i<13;i++){
            if(c_num_open[i]%4<test.suit){
                nb_card++;
            } else{
                break;
            }
        }
        if(local_card==0){
            result=rand()%(13-process);
        }else{
            result=nb_card+(rand()%local_card);
        }
        //rintf("result: %d\n",result);
        //printf("\n2.%d %d\n",nb_card,local_card);
        test.c_played[test.num_user]=c_num_open[result];
        return result;
    }
}


int rp_close(int flag)
{
    //printf("NOW random close.\n");
    int nb_card=0,local_card=0;
    int i,result;
    nb_card=c_close();
    if(flag==1){ // flag - 1 means first to play
        result=rand()%nb_card;
        //printf("Nb_card.%d\n",nb_card);
        test.suit=c_num_close[result]%4;
        test.c_played[test.num_user]=c_num_close[result];
        return result;
    }
    else {
        for(i=0;i<39;i++){
            if(c_num_close[i]%4==test.suit){
                local_card++;
            }
        }
        nb_card=0;
        for(i=0;i<39;i++){
            if(c_num_close[i]%4<test.suit){
                nb_card++;
            } else{
                break;
            }
        }
        if(local_card==0){
            result=rand()%(39-process*3);
        }else{
            result=nb_card+(rand()%local_card);
        }
        /*if(local_card==0){
            if(nb_card==0){
                result=rand()%(39-process*3);
            }else{
                int temp;
                do{
                    temp=rand()%(39-process*3);
                }while (temp>nb_card && temp<(nb_card+local_card));
                if(temp<nb_card){
                    result=rand()%nb_card;
                }else{
                    result=rand()%(temp-nb_card-local_card+1)+(nb_card+local_card);
                }
            }
        }else{
            result=nb_card+(rand()%local_card);
        }
        */
        //printf("\n2.%d %d\n",nb_card,local_card);
        test.c_played[test.num_user]=c_num_close[result];
        return result;
    }
}


int c_open() //calling cards
{
    test.num_user%=4;
    int i,j=0;
    for(i=0;i<13;i++){
        c_num_open[i]=-1;
    }
    for(i=0;i<13;i++){
        if(Users_Nums[test.num_user][i]!=-1){
            c_num_open[j++]=Users_Nums[test.num_user][i];
        }
    }
    //printf("Call cards open success. Return %d cards.\n",j);
    return j;
}

int c_close()
{
    test.num_user%=4;
    int i,j=0;
    for(i=0;i<13;i++){
        c_num_close[i]=-1;
    }
    for(i=0;i<39;i++){
        if(User_Unknown[test.num_user][i]!=-1){
            c_num_close[j++]=User_Unknown[test.num_user][i];
        }
    }
    //printf("Call cards closed success. Return %d cards.\n",j);
    return j;
}


int cc(int num_user) //compare cards
{
    int i,max=-1;
    int winner_s=-1;
    int verified[4]={-1,-1,-1,-1};
    for(i=0;i<4;i++){
        if(test.c_played[i]%4==test.suit){
            verified[i]=test.c_played[i]/4;
        }
    }
    for(i=0;i<4;i++){
        if(verified[i]>max){
            max=verified[i];
            winner_s=i;
        }
    }
    /*
    printf("user played cards.\n");
    for(i=0;i<4;i++){
        printf("%d -- %s%s\t",i,Suits_name[a.p_card[i]%4],Height[a.p_card[i]/4]);
    }
    printf("\n");
     */
    if (winner_s == num_user){
        return 1;
    } else {
        return 0;
    }
}



int min_card() //get the min card
{
    //printf("Minimize activated.\n");
    int i,count=0,min,result=-2;
    for(i=0;i<13;i++){
        if(Users_Nums[test.num_user][i]%4==test.suit && test.suit!=-1) count++;
    }
    min=13;
    c_open();
    if(count==0){
        for(i=0;i<13;i++){
            if(Users_Nums[test.num_user][i]!=-1 && Users_Nums[test.num_user][i]/4<min){
                min=Users_Nums[test.num_user][i]/4;
                count=Users_Nums[test.num_user][i];
            }
        }
        //printf("Minimize non local\n");
        for(i=0;i<13;i++){
            if(c_num_open[i]==count){
                return i;
            }
        }
        return -1;
    }else{
        for(i=0;i<13;i++){
            if(c_num_open[i]/4<min && c_num_open[i]%4==test.suit){
                min=c_num_open[i]/4;
                result=i;
                //printf("Now last result is %d\t",result);
            }
        }
        //if(print_func[0]==1) printf("Minimize local -- %d.%c -- %d.%c\n",test.suit,Suits_name[test.suit],test.num_user,U_N[test.num_user]);
        return result;
    }
}

/*
    struct simulate{
    int suit;
    int flag;
    int c_played[4];
    int num_user;
    };
 */

int simulation(int times,int num_user) { //simulation of Monte_carol
    //float time;
    //printf("Stimulation start.\n");
    int result_code=0;
    int win_num[13]={0};
    int total_num[13]={0};
    float max=0;
    int i,j;
    original.flag=0;
    for(i=0;i<4;i++){
        original.c_played[i]=Cards_played[i];
        if(Cards_played[i]==-1) original.flag++;
    }
    original.num_user=num_user;
    original.suit=local_suit;
    int card=-1,result=-1;
    for(i=0;i<times;i++){
        p_test=memcpy(p_test,p_orig, sizeof(struct simulate));
        //start_simulate=clock();
        if(test.flag==4){
            card = rp_open(1);
            test.num_user++;
            test.flag--;
        }
        for(j=0;j<test.flag;j++,test.num_user++){
            if(test.num_user==num_user){
                card = rp_open(0);
            }else{
                if(game==2){
                    rp_open(0);
                } else{
                    rp_close(0);
                    //printf("Random close success.\n");
                }
            }
        }
        //time=(float)(clock()-start_simulate)/CLOCKS_PER_SEC;
        if(cc(num_user)==1){
            //printf("Check. win_num %d -- ",card+1);
            //for(i=0;i<4;i++) printf("%c%c\t",Suits_name[test.c_played[i]%4],Height[test.c_played[i]/4]);
            //printf("\n");
            win_num[card]++;
            total_num[card]++;
        }else{
            total_num[card]++;
        }
        //printf("Stimulation No.%d -- %d\n",i+1,card);
    }
    for (i=0;i<13;i++){
        if(((float)win_num[i]/(float)total_num[i])>max){
            max=(float)win_num[i]/(float)total_num[i];
            result=i;
            result_code=1;
        }
    }
    if(print_func[0]) printf("max = %.2f\n",max);
    if(max<0.2){
        p_test=memcpy(p_test,p_orig, sizeof(struct simulate));
        result=min_card();
        if(print_func[0]) printf("Mini result %d\n",result+1);
        //system("read -p 'Press Enter to continue...'");
        result_code=2;
    }
    if(print_func[0]) printf("Simulation: %d.%c%c\n\n",
            result_code,Suits_name[Users_Nums[num_user][result]%4],Height[Users_Nums[num_user][result]/4]);
    // printf("Simulate %d times -- %.6fs\n",times,time);
    return result;
}