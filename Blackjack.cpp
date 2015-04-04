//program name:Blackjack
//It's the classic 21 point game.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string deck[4][13]; //represent the deck,52 cards in total
double deckvalue[13]; //shows the value of each card
double sum1, sum2; //sum1 is the sum of player's value while sum2 is the sum of computers
int dealt[4][13] = {0}; //shows whether this card has been used. 0 means unused
string player_cards = "", computer_cards = ""; //store player and computer's card
int num1, num2; //count how many cards player and computer own
bool mark; 

void create_deck(), deal1(), deal2(), player_phase(), computer_phase(), judge(), initalize();

void create_deck(){ //create a deck
	char heart = 3, diamond = 4, club = 5, spade = 6; //code in computer. if your computer cannot show this,please replace it.
	string H, D, C, S;
	string color[4] = {H=heart,D=diamond,C=club,S=spade}; //elements in array is string 
	char start = '1';
	for (int i=0;i<4;++i){
		for (int j=0;j<10;++j){
			char num = start + j; //turn int into char
			deck[i][j] = color[i] + num; //since it's string, + means join two parts together
		}
		deck[i][0] =color[i] + "A";
		deck[i][9] =color[i] + "10";
		deck[i][10] =color[i] + "J";
		deck[i][11] =color[i] + "Q";
		deck[i][12] =color[i] + "K";
	}
	for (int i=0;i<13;++i){
		deckvalue[i] = i + 1; //store the value of each card
	}
	deckvalue[10] = deckvalue[11] = deckvalue[12] = 0.5;
}

void initalize(){ //initialize all. 
	create_deck();
	int dealt[4][13] = {0};
	player_cards = "";
	computer_cards = "";
	sum1 = 0, sum2 = 0; 
	num1 = 0, num2 = 0;
	mark = true;
}

void deal1(){ //deal to player
	srand(time(NULL));
	int row, column;
	do{
		row = rand() % 4;
		column = rand() % 13;
	}while(dealt[row][column] == 1); //repeat until the card is unused
	player_cards += (deck[row][column] + " "); 
	dealt[row][column] = 1; //after used, 0 changes into 1
	sum1 += deckvalue[column]; //player sum change
	num1 +=1; //card number +1
}

void deal2(){ //deal to computer,almost same to the formal one
	srand(time(NULL));
	int row, column;
	do{
		row = rand() % 4;
		column = rand() % 13;
	}while(dealt[row][column] == 1);
	computer_cards += (deck[row][column] + " "); 
	dealt[row][column] = 1;
	sum2 += deckvalue[column];
	num2 +=1;
}

void player_phase(){
	cout << "player's phase" << endl;
	cout  << "player's cards" << " ";
	deal1();deal1();
	cout << player_cards << " total number:" << sum1 << endl;
    	
	bool flag = true;
	string choice;
    while (flag){ //repeat until the player doesn't want card any more   	
		
		bool flag1 = 0;	//this part use try-catch method to vertify the input	
		do{ 
			try {
				cout << "Another card? (y/n)";
				getline(cin, choice);
				if(choice != "Y" && choice != "y" && choice != "N" && choice != "n"){
					throw ("invalid input! please input y/n!");
				}else{
					flag1 = 1;
					}
    			}catch (const char *err_msg)
    			{
        			cout << err_msg <<endl;
    			}
			}while(flag1 == 0); //until the input is valid
			
    	if (choice == "Y"||choice == "y"){
    		deal1();
    		cout << "Another card get! " << player_cards << " total number:" << sum1 <<endl;
			if (sum1 > 21){ //if your sum grater than 21,you lose
				cout << endl << "YOU LOSE!" << endl;
				mark = false; //since you have lost,the following step is no need. this mark is used for this reason.
				break;
			}    	
		}else{
			flag = false;
			cout << endl;
		}
	} 	
}

void computer_phase(){
	cout << "computer's phase" << endl;
	cout  << "computer's cards" << " ";
	deal2();deal2();
	cout << computer_cards << " total number:" << sum2 << endl;
	while (sum2 < sum1||(sum1 == sum2 && num2 < num1)){ //computer will continue until its sum is greater or total is equal but card number is less
		deal2();
		cout << "Another card get! " << computer_cards << " total number:" << sum2 << endl;
	}	
}

void judge(){ //judge who wins
	if (sum1 == 21 && sum2 ==21 && num1 == num2){ //being such a case,reach a draw
		cout << "A DRAW!" << endl;
	} 
	else{
	if (sum2 > 21){
		cout << endl << "YOU WIN!" << endl;
	}else{
		cout << endl << "YOU LOSE!" << endl;
	} 
	}
}

int main(){ //now it's easy to understand
	string choice;
	do{
	initalize();
	player_phase();
	if (mark){
		computer_phase();
		judge();
	}
	
	bool flag1 = 0;	
	do{
		try {
			cout << endl << "Another try? (y/n)";
			getline(cin, choice);
			if(choice != "Y" && choice != "y" && choice != "N" && choice != "n"){
				throw ("invalid input! please input y/n!");
			}else{
				flag1 = 1;
				}
    		}catch (const char *err_msg)
    		{
        		cout << err_msg <<endl;
    		}
		}while(!flag1);
	
	cout << endl;
	}while(choice == "Y"||choice == "y");
	return 0;
}

