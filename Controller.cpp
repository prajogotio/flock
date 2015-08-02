#include "flock.h"
#include <iostream>

namespace flock{

Controller::Controller():
	window(sf::VideoMode(1024, 640), "Flock"),
	player(512, 320),
	currentCommand(),
	commandBuffer(CommandType::Move)
	{}

void Controller::run() {
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::A) {
					commandBuffer = CommandType::Smaller;
				}
				if(event.key.code == sf::Keyboard::S) {
					commandBuffer = CommandType::Bigger;
				}
				if(event.key.code == sf::Keyboard::D) {
					commandBuffer = CommandType::Slower;
				}
				if(event.key.code == sf::Keyboard::F) {
					commandBuffer = CommandType::Faster;
				}
				if(event.key.code == sf::Keyboard::E) {
					commandBuffer = CommandType::Add;
				}
				if(event.key.code == sf::Keyboard::R) {
					commandBuffer = CommandType::Remove;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				commandBuffer = CommandType::Move;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					currentCommand.type = commandBuffer;
					currentCommand.x = event.mouseButton.x;
					currentCommand.y = event.mouseButton.y;
				}
			}

		}
		//handleCommands();
		update();
		render();
	}
}

void Controller::handleCommands() {
	// CommandType type = CommandType::Move;
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	// 	type = CommandType::Smaller;
	// }
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	// 	type = CommandType::Bigger;
	// }
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	// 	type = CommandType::Slower;
	// }
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
	// 	type = CommandType::Faster;
	// }
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
	// 	type = CommandType::Add;
	// }
	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
	// 	type = CommandType::Remove;
	// }
	// if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	// 	sf::Vector2i pos = sf::Mouse::getPosition(window);
	// 	currentCommand.type = type;
	// 	currentCommand.x = pos.x;
	// 	currentCommand.y = pos.y;
	// } else {
	// 	currentCommand.type = CommandType::None;
	// }
}

void Controller::update() {
	if(currentCommand.type == CommandType::Move) player.moveTo(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Smaller) player.makeSmaller(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Bigger) player.makeBigger(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Slower) player.makeSlower(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Faster) player.makeFaster(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Add) player.add(currentCommand.x, currentCommand.y);
	if(currentCommand.type == CommandType::Remove) player.remove(currentCommand.x, currentCommand.y);
	player.updateState();
	currentCommand.type = CommandType::None;
	//std::cout << "command at (" << currentCommand.x << ", " << currentCommand.y << ")" << std::endl;
}

void Controller::render() {
	window.clear(sf::Color(255, 255, 255));
	auto& sprites = player.getSprites();
	for (const auto& sprite : sprites) {
		sf::CircleShape shape(sprite.getSize()/2);
		shape.setFillColor(sf::Color(0, 0, 0));
		shape.setPosition(sprite.getX() - sprite.getSize()/2, sprite.getY() - sprite.getSize()/2);
		window.draw(shape);
	}
	window.display();
}
}