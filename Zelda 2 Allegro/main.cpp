#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Display.h"
#include "Npc.h"
#include "Grid.h"
#include "Wosu.h"
#include "Guma.h"
#include "Ball.h"
#include "Stalfos.h"
#include "Items.h"
#include "GameLoop.h"

int main() {
	app::App appl;
	appl.Main();
	return 0;
}