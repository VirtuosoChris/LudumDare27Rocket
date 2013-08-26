#ifndef GAME_CODE_H_INCLUDED
#define GAME_CODE_H_INCLUDED
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

enum orientation {left, middle, right};

//struct for switches and lights
struct game_objects{
	float x;
	float y;
	int orientation;
	unsigned int state;

};


void loadSwitches(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);
void handleInput(float x, float y, std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);
void setLights(std::vector<struct game_objects> &switches, std::vector<struct game_objects> &lights);

extern std::vector<struct game_objects> switches;
extern std::vector<struct game_objects> lights;

#endif
