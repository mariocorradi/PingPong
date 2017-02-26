#include "Game.h"
#include <memory>

int main(int argc, char* args[])
{
	
	 auto gameLoop = std::make_shared<Game>(480,320);
	
	 //puntatore
	 
	 gameLoop->Run();

	 /*while (g.Run())
	{

	}*/
	
	return 0;
}
