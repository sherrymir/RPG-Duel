#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class Entity{
private:
	string Name;
	int Health;
	int Damage;
	int Defense;
public:
	void setName(string name);
	string getName();
	void setHealth(int health);
	int getHealth();
	void setDamage(int damage);
	int getDamage();
	void setDefense(int defense);
	int getDefense();
	
	Entity(string name,int health, int damage, int defense);
	
	virtual void Attack(Entity& target) = 0;
	void DisplayHealth();
	void DisplayDefense();
	void DamageTaken(int damage);
	
};
//intilized constructor for the game
Entity::Entity(string name,int health,int damage , int defense) : Name(name),Health(health),Damage(damage),Defense(defense){}

void Entity::setName(string name){
	Name = name;
}
string Entity::getName(){
	return Name;
}
void Entity::setHealth(int health){
	Health = health;
}
int Entity::getHealth(){
	return Health;
}
void Entity::setDamage(int damage){
	Damage = damage;
}
int Entity::getDamage(){
	return Damage;
}
void Entity::setDefense(int defense){
	Defense = defense;
}
int Entity::getDefense(){
	return Defense;
}

void Entity::DisplayHealth(){
	cout<<Name<<" Health : "<<Health<<endl;	
}
void Entity::DamageTaken(int damage){			//intilized damagetaken for eh damage-taken while defense is up 
	int EffectiveDamage = damage - Defense;		//for that i created another variable for flexiblity
	if(EffectiveDamage < 0){
		EffectiveDamage = 0;
	}
	Health -= EffectiveDamage;
	if(Health < 0){
		Health = 0;
		cout<<Name<<" Has died"<<endl;
	}
}

//----------------------------------------------------------------------		 PLAYER		  --------------------------------------------------------------------------------//

class Player:public Entity{
private:
	int Ability;
	bool special_move_used; //created this to put limit on ability
	bool defense_used;		//created this to put limit on defense(cuz it keeps going up,dk how to fix it)
public:
	void setAbility(int ability);
	int getAbility();
	
	Player(string name,int health, int damage , int defense, int ability); //declared constructed and added ability for player
	void Attack(Entity& target);
	void Defend();
	void SpecialMove(Entity& target);
	
};

void Player::setAbility(int ability){Ability = ability;}
int Player::getAbility(){return Ability;}

Player::Player(string name,int health, int damage , int defense, int ability):Entity(name,health,damage,defense),Ability(ability){}

void Player::Attack(Entity& target){	//here i used refernce of the main class and created an object(for opponent),similarly to overloading function
	cout<<"\n";
	cout <<"=>"<< getName() <<" attacks "<<target.getName()<<" for "<<getDamage()<<" damage!"<<endl;
	target.DamageTaken(getDamage());
}
void Player::Defend(){
	if(!defense_used){
	cout<<getName()<<" is Defending"<<endl;
	setDefense(getDefense()+ 10);
	defense_used = true;
	}else{
		cout<<"Defense is already been used"<<endl;
	}
}
void Player::SpecialMove(Entity& target){	//here i again did the same thing 
	if(!special_move_used){					//here i putted the limit for special-move using bool which is member-class 
		cout<<"The "<<getName()<<" is using special move on "<<target.getName()<<" for "<<getDamage()+7<<" Damage!"<<endl;
		target.DamageTaken(getDamage());
		special_move_used = true;
	}else{
		cout<<"Special Move has been already used"<<endl;
	}
	
}

//----------------------------------------------------------------------		 ENEMY		  --------------------------------------------------------------------------------//

class Enemy:public Entity{
public:
	Enemy(string name,int health, int damage , int defense);
	void Attack(Entity& target);
};

Enemy::Enemy(string name,int health, int damage , int defense):Entity(name,health,damage,defense){} 
void Enemy::Attack(Entity& target){ //similarly,we did here
	cout <<"=>"<< getName() <<" attacks "<<target.getName()<<" for "<<getDamage()<<" damage!"<<endl;
	target.DamageTaken(getDamage());
}

//----------------------------------------------------------------------		 MAIN FUNCTION		  --------------------------------------------------------------------------------//

int main(){
	string input;
	cout<<"					   	FANSTASY BATTLE\n"<<endl;
do{
	//created a vector for flexible way to select and store characters
	vector<Player>players = {
	Player("SwordMaster", 250, 50, 30, 50), 
	Player("Mage", 200, 25, 5, 35),		 
	Player("Swordman", 220, 35, 20, 30),	 
	Player("Ninja", 180, 40, 10, 40) 
	
	};
	cout<<"=>Choose a Character"<<endl; //for displaying character list
	for(size_t i=0; i<players.size();i++){
		cout<<(i+1)<<". "<<players[i].getName()<<endl;
	};
	int Playerchoice; 
	cout<<"Enter the number of the character you want to play: ";
	cin>>Playerchoice;
	if(Playerchoice<1 || Playerchoice> players.size()){
		cout<<"Invalid choice."<<endl;
		return 0;
	}
	//created this to display the chosen character's stats
	cout<<"->You have chosen the class "<<players[Playerchoice - 1].getName()<<endl;	
	cout<<"Class: "<<players[Playerchoice - 1].getName()<<endl;
	cout<<"Health: "<<players[Playerchoice - 1].getHealth()<<endl;
	cout<<"Strength: "<<players[Playerchoice - 1].getDamage()<<endl;
	cout<<"Vitality: "<<players[Playerchoice - 1].getDefense()<<endl;
	

	//created a vector for flexible way to select and store Enemy data
	vector<Enemy>enemies = {
 	Enemy("Troll", 300, 40, 15),	 
	Enemy("Orc", 200, 35, 10),	   
	Enemy("Goblin", 100, 20, 5),	  
	Enemy("Barbarian", 150, 25, 8) 
	};
	
	cout<<"\n=>Choose an Enemy to Battle"<<endl;	//for displaying enemy list
	for(size_t i = 0;i<enemies.size();i++){
		cout<<(i+1)<<". "<<enemies[i].getName()<<endl;
	}
	int Enemychoice;
	cout<<"Enter the number of the Enemy you want to play against: ";
	cin>>Enemychoice;
	if(Enemychoice<1 || Enemychoice> enemies.size()){
		cout<<"Invalid choice."<<endl;
		return 1;
	}
	//created this to display the chosen opponent's stats
	cout<<"->You have chosen the "<<players[Playerchoice - 1].getName()<<" to fight against "<<enemies[Enemychoice - 1].getName()<<endl;
	cout<<"Name: "<<enemies[Enemychoice - 1].getName()<<endl;
	cout<<"Health: "<<enemies[Enemychoice - 1].getHealth()<<endl;
	cout<<"Strength: "<<enemies[Enemychoice - 1].getDamage()<<endl;
	cout<<"Vitality: "<<enemies[Enemychoice - 1].getDefense()<<endl;
	
	//here i created objects for both classess 
	Player& chosenplayer = players[Playerchoice - 1]; //[Playerchoice - 1] this to get the character from vector like(taking it and removing it from vector)
	Enemy& chosenenemy = enemies[Enemychoice - 1];	//vector is flexible way h owever, could also do without vector
	cout<<"\n				 "<<chosenplayer.getName()<<" VS "<<chosenenemy.getName()<<endl; //show-down
	
	//can also used do-while...just wanted to try something different
	//when the health of any or both of the entities get to zero the loop will terminate
	while(chosenplayer.getHealth()>0 && chosenenemy.getHealth()>0){
		int action;
		cout<<"\n1. Attack \n2.Defend \n3.Special Move \nEnter your choice: ";
		cin>>action;
		if(action == 1){
			chosenplayer.Attack(chosenenemy);
			cout<<chosenenemy.getName()<<" Remaining health: "<<chosenenemy.getHealth()<<endl;
		}else if(action == 2){
			chosenplayer.Defend();
		}else if(action == 3){
			chosenplayer.SpecialMove(chosenenemy);
			cout<<chosenenemy.getName()<<" Remaining health: "<<chosenenemy.getHealth()<<endl;
		}else{
			cout<<"Invalid action.You have used your turn"<<endl;
			continue;
		}
		
		if(chosenenemy.getHealth()>0){
			chosenenemy.Attack(chosenplayer);
			cout<<chosenplayer.getName()<<" Remaining health: "<<chosenplayer.getHealth()<<endl;
		}
	}
	
	//when the health reaches 0 this loop will start
	if (chosenplayer.getHealth() > 0 && chosenenemy.getHealth()==0){
		cout<<chosenplayer.getName()<<" has defeated the "<<chosenenemy.getName()<<endl;
		cout<<"You won"<<endl;
	}else if (chosenplayer.getHealth() == 0 && chosenenemy.getHealth()>0){
		cout<<chosenenemy.getName()<<" has defeated the "<<chosenplayer.getName()<<endl;
		cout<<"You have died"<<endl;
	}else{
		cout<<"Due to the Heavy battle and prolonged battle between "<<chosenplayer.getName()<<" and "<<chosenenemy.getName()<<" characters are critically damage."<<endl;
		cout<<"This is a draw";
	}
	cout<<"Do you wanna play this game?(Yes/NO)"<<endl;
	cout<<"A. ";
	cin>>input;
	transform(input.begin(),input.end(),input.begin(), ::tolower);
}while(input == "yes"); 

}