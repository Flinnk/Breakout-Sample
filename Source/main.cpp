#include <Core\Engine.h>
#include "App.h"
#include <stdlib.h>

namespace GameEngine {
	Application* GetApplicationInstance() {
		return new App();
	}
}


int main() 
{
	GameEngine::Engine::GetInstance().Run();
	return 0;
}


