#include "Game.h"
#include <memory>

int main(int argc, char* args[])
{
	 Game g(800, 640);
	 auto gameLoop = std::make_shared<Game>(800,600);
	
	 //puntatore
	 
	 gameLoop->Run();

	 /*while (g.Run())
	{

	}*/
	
	return 0;
}
