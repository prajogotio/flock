#ifndef _FLOCK_CONTROLLER_H
#define _FLOCK_CONTROLLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

namespace flock {

class Controller {
public:
	Controller();
	void run();
private:
	enum class CommandType {
		Move,
		Faster,
		Slower,
		Bigger,
		Smaller,
		Add,
		Remove,
		None
	};

	struct Command {
		CommandType type;
		double x;
		double y;
		Command(CommandType type_, double x_, double y_):
			type(type_), x(x_), y(y_) {}
		Command():
			type(CommandType::None), x(0), y(0) {}
	};

	sf::RenderWindow window;
	Player player;
	Command currentCommand;
	CommandType commandBuffer;
	
	void update();
	void render();
	void handleCommands();
};

}

#endif