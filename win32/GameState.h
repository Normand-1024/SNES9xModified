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

class GameState {
public:
	GameState() {
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

	virtual void updateState() = 0;

	virtual void printState() = 0;

private:

	stringstream ss;
};