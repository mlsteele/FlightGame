/// \mainpage FlightGame Docs
/// \section FlightGame
/// This is it, man!

#include <iostream>
#include "FlightGame.h"

int main(int argc, char** argv) {
  glutInit(&argc, argv);

	FlightGame game;
	int result = game.Execute();

	return result;
}
