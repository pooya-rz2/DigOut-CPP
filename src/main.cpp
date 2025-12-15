/////////////////////////////////////////libraries
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include <cstdlib>
#include <sstream>
using namespace std;
/////////////////////////////////////////global variables
bool life=1;
const int max_list_size=999;
const string player="! ",soil="# ",stone="@ ",coin="$ ",air="  ",potion="+ ",bomb="* ",robot="R ",power_potion="P ";
int record_number=0,x_player=0,y_player=0,score=0,power_potion_amount=20,potion_heal=30,bomb_damage=30,setting_player_power=40,robot_power=30,width=8,height=4,stone_number=4,coin_number=1,bomb_number=2,potion_number=1,robot_number=1,power_potion_number=1,robot_setting_health=80,setting_health=100,health,player_power;
string player_name;
int *robots_health;
int *robots_x_address;
int *robots_y_address;
string player_names[max_list_size];
int player_scores[max_list_size];
string block[max_list_size][max_list_size];
/////////////////////////////////////////functions
void open_setting();
void inform();
void update_object_effects(char movement);
void game_menu();
void generate_environment();
void print();
void check_gravity_effect();
void read_data();
void gravity_effect();
void save_data();
void play_again_stats();
void swap_int();
void move();
void open_setting();
void open_record();
void play();
void show_result();
void order_records();
void update_records();
void swap(string* a,string* b);
int wich_robot(int x_robot,int y_robot);
void fight_with_robot(int x_robot,int y_robot);


int main() 
{
	inform();
	read_data();
	game_menu();
	save_data();
	return 0;
}

void inform()
{
	cout<<"welcome...\n"<<"use a-s-d-w to move and j-k-l-i to dig\n"<<"you should catch dollar signs\n"<<"try not to get under stone cause it kills you\n"<<"potions(+) heal your health and bombs(*) decrease it\n"<<"robots(R) fight with you if uou enter their block and you can increase your power by power potions(P) \n"<<"press any key to countinue...\n";
	_getch();
	system("CLS");
}
 
void read_data()
{
string string_data,string_data2;
int counter=0,counter2=0,data;

ifstream myreadfile("string.data.txt");
while (getline (myreadfile, string_data2)) 
{ 
	player_names[counter2]=string_data2;
	counter2++;
}
myreadfile.close();

ifstream MyReadFile("data.txt");
while (getline (MyReadFile, string_data)) 
{ 
    stringstream ss;  
  	ss << string_data;  
  	ss >> data;
	if(counter==0) width=data;
	else if(counter==1) height=data;
	else if(counter==2) stone_number=data;
	else if(counter==3) coin_number=data;
	else if(counter==4) bomb_number=data;
	else if(counter==5) potion_number=data;	
	else if(counter==6) robot_number=data;	
	else if(counter==7) power_potion_number=data;	
	else if(counter==8) setting_health=data;
	else if(counter==9) robot_setting_health=data;	
	else if(counter==10) player_power=data;	
	else if(counter==11) robot_power=data;	
	else if(counter==12) potion_heal=data;	
	else if(counter==13) bomb_damage=data;	
	else if(counter==14) power_potion_amount=data;	
	else if(counter==15) record_number=data;	
	else if(counter>15)  player_scores[counter-16]=data;
	counter++;
}
MyReadFile.close();
}

void game_menu()
{
	char num;
		system("CLS");
		cout<<"press one of below numbers\n"<<"1. Start Game\n"<<"2. Setting\n"<<"3. Records\n"<<"4. Exit :(\n";
		num=_getch();

	switch(num)
	{
		case '1':
			play();
			update_records();
			save_data();
			break;
		case '2':
			open_setting();
			save_data();
			break;
		case '3':
			open_record();
			break;
		case '4':
			save_data();
			exit(0);
		default :
			game_menu();
			break;	
	}
	game_menu();

}

void play()
{
	system("CLS");
	play_again_stats();
	cout<<"so what is your name?\npress enter after type...\n";
	cin>>player_name;
	system("CLS");
	generate_environment();
	while(life==1 && score!=coin_number)
	{
		print();
		move();
		gravity_effect();
		check_gravity_effect();
		gravity_effect();
		system("CLS");
	}
	show_result();
	update_records();
	save_data();
	cout<<"press any button to countinue...\n";
	_getch();
	system("CLS");
	game_menu();
}

void play_again_stats()
{
	life=1;
	score=0;
	x_player=0;
	y_player=0;
	health=setting_health;	
	player_power=setting_player_power;
}

void generate_environment()
{
	int satr_random,sotun_random;
	srand(time(0));
	///////////////////////////////////////soil_unit(s) pos
	for(int i=0 ; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			block[i][j]=soil;
		}
	}
	///////////////////////////////////////player pos
	block[x_player][y_player]=player;
	///////////////////////////////////////stone(s) random pos
	for(int i=0;i<stone_number;i++)
	{
		satr_random=rand()%height;
		sotun_random=rand()%width;
		if(block[satr_random][sotun_random]==soil) block[satr_random][sotun_random]=stone;
		else i--;
	}
	///////////////////////////////////////coin(s) random pos
	for(int i=0;i<coin_number;i++)
	{
		satr_random=rand()%height;
		sotun_random=rand()%width;
		if(block[satr_random][sotun_random]==soil && block[satr_random-1][sotun_random]!=stone) block[satr_random][sotun_random]=coin;
		else i--;
	}
	///////////////////////////////////////bomb(s) random pos
	for(int i=0;i<bomb_number;i++){
		satr_random=rand()%height;
		sotun_random=rand()%width;
		if(block[satr_random][sotun_random]==soil) block[satr_random][sotun_random]=bomb;
		else i--;
	}
	///////////////////////////////////////potion(s) random pos
	for(int i=0;i<potion_number;i++){
		satr_random=rand()%height;
		sotun_random=rand()%width;
		if(block[satr_random][sotun_random]==soil) block[satr_random][sotun_random]=potion;
		else i--;
	}
	///////////////////////////////////////power potion(s) random pos
	for(int i=0;i<power_potion_number;i++){
		satr_random=rand()%height;
		sotun_random=rand()%width;
		if(block[satr_random][sotun_random]==soil) block[satr_random][sotun_random]=power_potion;
		else i--;
	}
	///////////////////////////////////////robot(s) random pos
	robots_health=new int[robot_number];
	robots_x_address=new int[robot_number];
	robots_y_address=new int[robot_number];
	for(int i=0;i<robot_number;i++){
		satr_random=rand()%height;
		sotun_random=rand()%width;
			if(block[satr_random][sotun_random]==soil) {
			block[satr_random][sotun_random]=robot;
			robots_health[i]=robot_setting_health;
			robots_x_address[i]=satr_random;
			robots_y_address[i]=sotun_random;
		}
		else i--;
	}
}

void check_gravity_effect()
{
	
	/////////////////////////////////////////////////////////////////////check player
	if(block[x_player-1][y_player]==coin  && x_player>0)
	{
		score++; // nice
		block[x_player-1][y_player]=air;
	}
	else if(block[x_player-1][y_player]==bomb  && x_player>0)
	{
		health-=bomb_damage; // :(
		block[x_player-1][y_player]=air;
	}
	else if(block[x_player-1][y_player]==potion  && x_player>0)
	{
		health+=potion_heal; // :) 
		block[x_player-1][y_player]=air;
	}
	else if(block[x_player-1][y_player]==power_potion  && x_player>0)
	{
		player_power+=power_potion_amount; // :} 
		block[x_player-1][y_player]=air;
	}
	else if(block[x_player-1][y_player]==robot  && x_player>0)		            fight_with_robot(x_player-1,y_player); // fight well
	else if((block[x_player-1][y_player]==stone  && x_player>0) || health<=0)	life=0; // :_) gg
	
	/////////////////////////////////////////////////////////////////////check robot
	////bomb on robots
	for(int i=0;i<robot_number;i++)
	{
		if(block[robots_x_address[i]-1][robots_y_address[i]]==bomb  && robots_x_address[i]>0)
		{
			robots_health[i]-=bomb_damage;
			block[robots_x_address[i]-1][robots_y_address[i]]=air;
			if (robots_health[i]<=0) block[robots_x_address[i]][robots_y_address[i]]=air;
		}
	}
	////stone on robots
	for(int i=0;i<robot_number;i++)
	{
		if(block[robots_x_address[i]-1][robots_y_address[i]]==stone  && robots_x_address[i]>0)
		{
			block[robots_x_address[i]][robots_y_address[i]]=air;
		}
	}
	
	
}

void gravity_effect()
{
int c;
for(int i=0 ; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			if((block[i][j]!=soil) && (block[i][j]!=air) && (block[i][j]!=player) && i<(height-1) && block[i+1][j]==air)	
			{
				for(c=1;c<=i;c++)
				{
					if(block[i-c][j]==air || block[i-c][j]==soil || block[i-c][j]==player) break;
					
				}
				for(int z=0;z<c;z++)
				{
					/////////////////////////////////update robot coordination
					if(block[i-z][j]==robot)
					{
						int n=wich_robot(i-z,j);
						robots_x_address[n]++;
					}
					swap(&block[i-z][j],&block[i-z+1][j]);
				}
				
				
			}
			
		}
	}
}

 void print()
{
 	for(int i=0 ; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			cout<<block[i][j];
		}
		cout<<"\n";
	}	
	cout<<"SCORE : "<<score<<"\n";
	cout<<"HEALTH : "<<health<<"\n";
 }

void move()
{
	char movement;
	movement=_getch();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////simple moves
	if((movement=='a' || movement=='A') && y_player>0 && (block[x_player][y_player-1]!=stone)  && (block[x_player][y_player-1]!=soil)) 
	{
		update_object_effects('a');
		swap(&block[x_player][y_player],&block[x_player][y_player-1]);	
		y_player-=1;	
	}
	
	else if((movement=='d' || movement=='D') && y_player<(width-1) && (block[x_player][y_player+1]!=stone)  && (block[x_player][y_player+1]!=soil)) 
	{
		update_object_effects('d');
		swap(&block[x_player][y_player],&block[x_player][y_player+1]);
		y_player+=1;
	}
	
	else if((movement=='w' || movement=='W') && x_player>0 && (block[x_player-1][y_player]!=stone)  && (block[x_player-1][y_player]!=soil)) 
	{
		update_object_effects('w');
		swap(&block[x_player][y_player],&block[x_player-1][y_player]);	
		x_player-=1;
	}
	
	else if((movement=='s' || movement=='S') && x_player<(height-1) && (block[x_player+1][y_player]!=stone)  && (block[x_player+1][y_player]!=soil))
	{
		update_object_effects('s');
		swap(&block[x_player][y_player],&block[x_player+1][y_player]);	
		x_player+=1;
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////digging
	else if((movement=='j' || movement=='J') && y_player>0 && (block[x_player][y_player-1]==soil))
	{
		block[x_player][y_player-1]=air;
	}
	else if((movement=='l' || movement=='L') && y_player<(width-1) && (block[x_player][y_player+1]==soil))  
	{
		block[x_player][y_player+1]=air;
	}
	else if((movement=='i' || movement=='I') && x_player>0 && (block[x_player-1][y_player]==soil))
	{
		block[x_player-1][y_player]=air;
	}
	else if((movement=='k' || movement=='K') && x_player<(height-1) && (block[x_player+1][y_player]==soil))
	{
		block[x_player+1][y_player]=air;
	}
	
}

void swap(string* a,string* b)
{
	string temp = *a;
	*a = *b;
	*b = temp;
}

void swap_int(int* a,int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void update_object_effects(char movement)
{
	switch(movement)
	{
		case 'a':
			if(block[x_player][y_player-1]==coin)
			{
				score++;
				block[x_player][y_player-1]=air;
			}
			else if(block[x_player][y_player-1]==bomb)
			{
				health-=bomb_damage;
				block[x_player][y_player-1]=air;
			}
			else if(block[x_player][y_player-1]==potion)
			{
				health+=potion_heal;
				block[x_player][y_player-1]=air;
			}
			else if(block[x_player][y_player-1]==power_potion)
			{
				player_power+=power_potion_amount;
				block[x_player][y_player-1]=air;
			}
			else if(block[x_player][y_player-1]==robot)
			{
				fight_with_robot(x_player,y_player-1);
			}break;
		case 'd':	
			if(block[x_player][y_player+1]==coin)
			{
				score++;
				block[x_player][y_player+1]=air;
			}
			else if(block[x_player][y_player+1]==bomb)
			{
				health-=bomb_damage;
				block[x_player][y_player+1]=air;
			}
			else if(block[x_player][y_player+1]==potion)
			{
				health+=potion_heal;
				block[x_player][y_player+1]=air;
			}
			else if(block[x_player][y_player+1]==power_potion)
			{
				player_power+=power_potion_amount;
				block[x_player][y_player+1]=air;
			}
			else if(block[x_player][y_player+1]==robot)
			{
				fight_with_robot(x_player,y_player+1);
			}break;
		case 'w':	
			if(block[x_player-1][y_player]==coin)
			{
				score++;
				block[x_player-1][y_player]=air;
			}
			else if(block[x_player-1][y_player]==bomb)
			{
				health-=bomb_damage;
				block[x_player-1][y_player]=air;
			}
			else if(block[x_player-1][y_player]==potion)
			{
				health+=potion_heal;
				block[x_player-1][y_player]=air;
			}
			else if(block[x_player-1][y_player]==power_potion)
			{
				player_power+=power_potion_amount;
				block[x_player-1][y_player]=air;
			}
			else if(block[x_player-1][y_player]==robot)
			{
				fight_with_robot(x_player-1,y_player);
			}break;
		case 's':	
			if(block[x_player+1][y_player]==coin)
			{
				score++;
				block[x_player+1][y_player]=air;
			}
			else if(block[x_player+1][y_player]==bomb)
			{
				health-=bomb_damage;
				block[x_player+1][y_player]=air;
			}
			else if(block[x_player+1][y_player]==potion)
			{
				health+=potion_heal;
				block[x_player+1][y_player]=air;
			}
			else if(block[x_player+1][y_player]==potion)
			{
				player_power+=power_potion_amount;
				block[x_player+1][y_player]=air;
			}
			else if(block[x_player+1][y_player]==robot)
			{
				fight_with_robot(x_player+1,y_player);
			}break;
	}
}

void fight_with_robot(int x_robot,int y_robot)
{
	int n=wich_robot(x_robot,y_robot);
	while(1)
	{
		robots_health[n]-=player_power;
		if(robots_health[n]<=0) 
		{
			///////////////////////////dont fight with your creator again
			block[x_robot][y_robot]=air;	
			break;
		}
		health-=robot_power;
		if(health<=0) 
		{
			////////////////////////////only robots will survive
			life=0;
			break;
		}
	}
}

int wich_robot(int x_robot,int y_robot)
{
	int i;
	for(i=0;i<robot_number;i++)
	{
		if((x_robot==robots_x_address[i]) && (y_robot==robots_y_address[i])) return i;
	}
}

void show_result()
{
	system("CLS");
	if(life) cout<<"you won ^_^\n";
	else
	{
		if(score==coin_number) cout<<"you died but u r still a winner *_*\n";
		else cout<<"you lost -_-\n";
	}

}

void update_records()
{
	int i;
	bool new_player=1;
	for(i=0;i<=record_number && (new_player);i++)
	{
		new_player=player_names[i].compare(player_name);
	}
	if(new_player)
	{
	player_names[record_number]=player_name;
	player_scores[record_number]=score;
	record_number++;
	}
	else
	{
		if(score>player_scores[i-1]) player_scores[i-1]=score;
	}
	order_records();
}

void order_records()
{
	for(int j=0;j<record_number;j++)
	{
		for(int k=j+1;k<record_number;k++)
		{
			if(player_scores[j]<player_scores[k]) 
			{
				swap_int(&player_scores[j],&player_scores[k]);
				swap(&player_names[j],&player_names[k]);
			}
			
		}
	}
	
}

void save_data()
{
ofstream myfile("data.txt");
myfile<<"";
myfile <<width<<endl<<height<<endl<<stone_number<<endl<<coin_number<<endl<<bomb_number<<endl<<potion_number<<endl<<power_potion_number<<endl<<robot_number<<endl<<setting_health<<endl<<robot_setting_health<<endl<<player_power<<endl<<robot_power<<endl<<potion_heal<<endl<<bomb_damage<<endl<<power_potion_amount<<endl<<record_number<<endl;
for(int i=0;i<record_number;i++)
{
	myfile <<player_scores[i]<<endl;	
}
myfile.close();	

ofstream file("string.data.txt");
file<<"";
for(int i=0;i<record_number;i++)
{
	file <<player_names[i]<<endl;	
}
file.close();		
}

void open_setting()
{
	char num,ch;
	int width_temp,height_temp,stone_num_temp,coin_num_temp,bomb_num_temp,potion_num_temp,health_temp,robots_health_temp,player_power_temp,robot_power_temp,potion_heal_temp,bomb_damage_temp,robot_number_temp,power_potion_number_temp,power_potion_amount_temp;

	system("CLS");
	cout<<"press one of below numbers\n"<<"1. Edit Width and Height\n"<<"2. Edit number of stones\n"<<"3. Edit number of coins\n"<<"4. Edit number of bombs\n"<<"5. Edit number of potions\n"<<"6. Edit number of power potions\n"<<"7. Edit number of robots\n"<<"8. Edit your health amount\n";
	cout<<"9. Edit robots health amount\n"<<"press (a) to Edit your power amount\n"<<"press (b) to Edit robot power amount\n"<<"press (c) to Edit bomb damage amount\n"<<"press (d) to Edit potion healing amount\n"<<"press (e) to Edit power increase in power potion\n"<<"press (z) to get back to the menu\n";
	num=_getch();
	system("CLS");
	switch(num)
	{
		case '1':
			system("CLS");
			cout<<"last width: "<<width<<"\ntype Width then press ENTENR\n";
			cin>>width_temp;
			system("CLS");
			cout<<"last height: "<<height<<"\ntype Height  then press ENTENR\n";
			cin>>height_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(((height_temp*width_temp)>(stone_number+coin_number+bomb_number+potion_number+power_potion_number+robot_number)) && height_temp>0 && width_temp)
				{
					height=height_temp;
					width=width_temp;	
				}
				else
				{
					system("CLS");
					cout<<"blocks are too small for objects defined.\n"<<"press any button to countinue...\n";
					_getch();
					system("CLS");
					break;
				}

			}
			system("CLS");
			break;
			
		case '2':
			system("CLS");
			cout<<"last stone number: "<<stone_number<<"\ntype new stone number then press ENTENR \n";
			cin>>stone_num_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_num_temp+coin_number+bomb_number+potion_number+power_potion_number+robot_number)) && stone_num_temp>0)
				{
					stone_number=stone_num_temp;	
				}
				else
				{
					system("CLS");
					cout<<"your stone number is unacceptble for blocks defined.\n"<<"press any button to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case '3':
			system("CLS");
			cout<<"last coin number: "<<coin_number<<"\ntype new coin number then press ENTENR\n";
			cin>>coin_num_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_number+coin_num_temp+bomb_number+potion_number+power_potion_number+robot_number)) && coin_num_temp>0)
				{
					coin_number=coin_num_temp;	
				}
				else
				{
					system("CLS");
					cout<<"your coin number is unacceptble for blocks defined.\n"<<"press any button to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case '4':
			system("CLS");
			cout<<"last bomb number: "<<bomb_number<<"\ntype new bomb number then press ENTENR\n";
			cin>>bomb_num_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_number+coin_number+bomb_num_temp+potion_number+power_potion_number+robot_number)) && bomb_num_temp>0)
				{
					bomb_number=bomb_num_temp;	
				}
				else
				{
					system("CLS");
					cout<<"your bomb number is unacceptble for blocks defined.\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case '5':
			system("CLS");
			cout<<"last potion number: "<<potion_number<<"\ntype new potion number then press ENTENR\n";
			cin>>potion_num_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_number+coin_number+bomb_number+potion_num_temp+power_potion_number+robot_number)) && potion_num_temp>0)
				{
					potion_number=potion_num_temp;
				}
				else
				{
					system("CLS");
					cout<<"your potion number is unacceptble for blocks defined.\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case '6':
			system("CLS");
			cout<<"last power potion number: "<<potion_number<<"\ntype new power potion number then press ENTENR\n";
			cin>>power_potion_number_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_number+coin_number+bomb_number+potion_number+power_potion_number_temp+robot_number)) && power_potion_number_temp)
				{
					power_potion_number=power_potion_number_temp;
				}
				else
				{
					system("CLS");
					cout<<"your power potion number is unacceptble for blocks defined.\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;	
			
		case '7':
			system("CLS");
			cout<<"last robots number: "<<robot_number<<"\ntype new robots number then press ENTENR\n";
			cin>>robot_number_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if((height*width>(stone_number+coin_number+bomb_number+potion_number+power_potion_number+robot_number_temp)) && robot_number_temp)
				{
					robot_number=robot_number_temp;
				}
				else
				{
					system("CLS");
					cout<<"your robot number is unacceptble for blocks defined.\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
		case '8':
			system("CLS");
			cout<<"last player health: "<<setting_health<<"\ntype new player health then press ENTENR\n";
			cin>>health_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(health_temp>0)
				{
					setting_health=health_temp;
				}
				else
				{
					system("CLS");
					cout<<"health should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case '9':
			system("CLS");
			cout<<"last robot health: "<<robot_setting_health<<"\ntype new robot health then press ENTENR\n";
			cin>>robots_health_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(robots_health_temp>0)
				{
					robot_setting_health=robots_health_temp;
				}
				else
				{
					system("CLS");
					cout<<"health should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case 'a':
			system("CLS");
			cout<<"last player power: "<<player_power<<"\ntype new player power then press ENTENR\n";
			cin>>player_power_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(player_power_temp>0)
				{
					player_power=player_power_temp;
				}
				else
				{
					system("CLS");
					cout<<"power should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case 'b':
			system("CLS");
			cout<<"last robot power: "<<robot_power<<"\ntype new robot power then press ENTENR\n";
			cin>>robot_power_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(robot_power_temp>0)
				{
					robot_power=robot_power_temp;
				}
				else
				{
					system("CLS");
					cout<<"power should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case 'c':
			system("CLS");
			cout<<"last potion healing amount: "<<potion_heal<<"\ntype new potion healing amount then press ENTENR\n";
			cin>>potion_heal_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(potion_heal_temp>0)
				{
					potion_heal=potion_heal_temp;
				}
				else
				{
					system("CLS");
					cout<<"healing amount should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
		case 'd':
			system("CLS");
			cout<<"last bomb damage amount: "<<bomb_damage<<"\ntype new bomb damage then press ENTENR\n";
			cin>>bomb_damage_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(bomb_damage_temp>0)
				{
					bomb_damage=bomb_damage_temp;
				}
				else
				{
					system("CLS");
					cout<<"bomb_damage should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
				
		case 'e':
			system("CLS");
			cout<<"last power potion,power increase : "<<power_potion_amount<<"\ntype new power potion,power increase amount then press ENTENR\n";
			cin>>power_potion_amount_temp;
			system("CLS");
			cout<<"save edits? \n"<<"y for YES / n for NO \n";
			ch=_getch();
			if(ch=='y' || ch=='Y')
			{
				if(power_potion_amount_temp>0)
				{
					power_potion_amount=power_potion_amount_temp;
				}
				else
				{
					system("CLS");
					cout<<"power should be a positive amount\n"<<"press any key to countinue...\n";
					_getch();
					system("CLS");
					break;
				}
			}
			system("CLS");
			break;
			
			case 'z':
				game_menu();	
			
	}
	open_setting();
}

void open_record()
{
	system("CLS");
	for(int i=0;i<record_number;i++)
	{
		cout<<player_names[i]<<"  -->  "<<player_scores[i]<<"\n";
	}
	cout<<"press any button to countinue...\n";
	_getch();
	system("CLS");
	game_menu();
}

////////////////////////////////////////////////////////////////thanks for attending/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////       gofatm 1k line she coole ;)      ////////////////////////////////////////////////////////
/////////////////////////////////////////////                mohammad mahdi rezazadeh               /////////////////////////////////////////////////