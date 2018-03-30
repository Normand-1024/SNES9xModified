#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <fstream>

#include "./port.h"
#include "./statemanager.h"
#include "./snapshot.h"
#include "memmap.h"
#include "wsnes9x.h"
#define ANNOYING_STATE_CLOCK 100

class SMWGameState {
public:
	SMWGameState() {
		//if (!stateMan.init(1024 * 1024 * 1024)) // 1 MB of buffer size
		//	fprintf(stdout, "\n INSUFFICIENT MEM SIZE IN STATEMAN \n");
	}

	void loadState() {
		std::stringstream temp;
		temp << ss.str();
		if (!UnfreezeState(ss))
			std::cout << "yer dun goofed" << std::endl;
		ss.swap(temp);
		}

	void saveState() {
		ss = FreezeState();
	}

	void updateState() {
		if (!levelLoaded) { 
			/* string into TCHAR array*/
			//std::string str_dir = "C:\\Users\\Henry\\Documents\\GitHub\\snes9x\\win32\\Saves\\Super Mario World (U) [!].srm";
			//TCHAR* dir = new TCHAR[str_dir.size() + 1];
			//dir[str_dir.size()] = 0;
			//std::copy(str_dir.begin(), str_dir.end(), dir);

			//LoadROM(dir, NULL);
			FreezeUnfreezeSlot(0, false); 
			levelLoaded = true;
			saveState();
			//Settings.FrameTime = 500;//4000;//FrameTimings[0];
			//ResetFrameTimer();
		}

		playerPosX = (Memory.RAM[0x95] << 8) + Memory.RAM[0x94];
		playerPosY = (Memory.RAM[0x97] << 8) + Memory.RAM[0x96];

		marioScore = (Memory.RAM[0xF36] << 16) + (Memory.RAM[0xF35] << 8) + Memory.RAM[0xF34];
		timer = Memory.RAM[0xF31] * 100 + Memory.RAM[0xF32] * 10 + Memory.RAM[0xF33];

		death = playerPosY > 60000;//(Memory.RAM[0xDDA] == 0xFF && playerPosY > 6000);
		levelComplete = (Memory.RAM[0xDDA] == 0xFF && Memory.RAM[0x13D9] == 2);

		clocktick++;
		if (clocktick >= ANNOYING_STATE_CLOCK) {
			//loadState();
			clocktick = 0;
			save = !save;
		}
	}

	void printState() {
		fprintf(stdout, "PosX << %d PosY << %d Score << %d Timer << %d Death << %d levelComplete << %d\n", playerPosX, playerPosY, marioScore, timer, death, levelComplete);
	}

private:
	int playerPosX;
	int playerPosY;

	int marioScore;
	int timer;
	
	bool levelLoaded;

	bool death;
	bool levelComplete;

	int clocktick = 0;
	bool save = false;

	stringstream ss;
};