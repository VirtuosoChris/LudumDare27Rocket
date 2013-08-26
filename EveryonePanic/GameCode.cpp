

#define LSD_W 24
#define LSD_H 16

#define LSU_W 22
#define LSU_H 17

#define MSD_W 15
#define MSD_H 16

#define MSU_W 14
#define MSU_H 14

#define RSD_W 14
#define RSD_H 15

#define RSU_W 16
#define RSU_H 15

//lights are the same
#define LIGHT_W 13
#define LIGHT_H 12

#include "GameCode.h"

bool wonGame= false;


std::vector<struct game_objects> switches;
std::vector<struct game_objects> lights;


void loadSwitches(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);
void handleInput(float x, float y, std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);
void setLights(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);

int notMain(){

	std::cout << "hello" << std::endl;



	loadSwitches(switches, lights);
	for(int i = 0; i<switches.size();i++){
			std::cout << "Orientation is " << switches.at(i).orientation;
			std::cout << " x is " << switches.at(i).x;
			std::cout << " y is " << switches.at(i).y << std::endl;
	}
	std::cout << "\n\n";

	float tempx, tempy;
	while(true){


		setLights(switches,lights);

		std::cout << "The state of the switches are:\n";
		for(int i = 0;i<switches.size();i++){
			std::cout << switches.at(i).state;
		}
		std::cout << "\n\n";
		std::cout << "The state of the lights are:\n";
		for(int i = 0;i<lights.size();i++){
			std::cout << lights.at(i).state;
		}
		std::cout << std::endl;

		std::cout << "Flip which switch (x followed by y)\n";
		std::cin >> tempx;
		std::cin >> tempy;

		handleInput(tempx, tempy, switches, lights);

		//switches.at(temp).state = !switches.at(temp).state;
	}
	system("PAUSE");
	return 0;
}


//handle setting up the game objects
void loadSwitches(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights)
{
	std::ifstream file;
	struct game_objects temp;
	std::string filename = "locations/left_switches";

	//Initialize switches
	for(int i =0; i<3;i++){
		file.open(filename);
		while(!file.eof()){
			file >> temp.x;
			file >> temp.y;

			switch(i)
			{
				case 0: temp.orientation = left;
						break;
				case 1: temp.orientation = middle;
						break;
				case 2: temp.orientation = right;
						break;
			}

			temp.state = 0;

			switches.push_back(temp);

		}
		file.close();
		//load the next file in order
		if(i == 0)
			filename = "locations/middle_switches";
		else if (i == 1)
			filename = "locations/right_switches";
	}
    std::ifstream file2;
	file2.open("locations/small_square_lights");


    while(!file2.eof()){
	//	if(!
       (file2 >> temp.x);
        //    std::cout << "err\n";
		//if(!
       (file2 >> temp.y);
           // ;;std::cout << "err\n";

		temp.state = 0;

		temp.orientation = orientation::left;

		lights.push_back(temp);

		// std::cout << "x is " << temp.x;
		//std::cout << " y is " << temp.y << std::endl;
		//system("PAUSE");
	}
	file2.close();

}

void setLights(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights)
{
	unsigned int seed=0x83b2371c;
	srand(seed);
	for(int i=0;i<switches.size();i++)
	{
	    unsigned int r=rand();
	    if(switches[i].state)
	    {
	        seed ^= r;
	    }
	}

	srand(seed);

    for(int j=0;j<lights.size();j++)
	{
        unsigned int r=rand();
        lights[j].state = r & 0x1;
	}
}

void handleInput(float x, float y, std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights)
{
	for(int i = 0; i < switches.size(); i++){
		int tempstate = 0;
		if(switches.at(i).state == 0)
			tempstate = 0;
		else
			tempstate = 1;

		int height = 0;
		int width = 0;

		//find which offset to use
		if (switches.at(i).x < 600){
			if (tempstate == 0){
				height = LSD_H;
				width = LSD_W;
			}
			else{
				height = LSU_H;
				width = LSU_W;
			}
		}
		else if (switches.at(i).x < 1400){
			if (tempstate == 0){
				height = MSD_H;
				width = MSD_W;
			}
			else {
				height = MSU_H;
				width = MSU_W;
			}
		}
		else {
			if (tempstate == 0){
				height = RSD_H;
				width = RSD_W;
			}
			else {
				height = RSU_H;
				width = RSU_W;
			}
		}

		//if the target is between the x bounds of the switch
		if((x <= (switches.at(i).x + ( height / 2))) && (x >= switches.at(i).x -(width / 2))){
			//and the target is between the y bounds of the switch
			if((y <= (switches.at(i).y + ( height / 2))) && (y >= switches.at(i).y -(width / 2))){
				//then flip the switch
				switches.at(i).state = !switches.at(i).state;
			}
		}
	}


}
