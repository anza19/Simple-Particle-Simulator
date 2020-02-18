#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace std;

const int SW = 800;
const int SH = 600;

int main(int argc, char* argv[]) {

	Screen screen;

	if (!screen.init()) {
		cout << "Could not init SDL" << endl;
		return -1;
	}


	//We need our game loop
	//until we have not quit the loop
	while (1) {
		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}