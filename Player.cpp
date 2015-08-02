#include "flock.h"
#include <vector>
#include <cmath>
#include <iostream>

namespace flock {

Player::Player(double x_, double y_):
	sprites(), 
	focusPoint(x_, y_) 
	{
		sprites.push_back(Sprite(x_, y_, InitialSize, InitialSpeed));
	}


void Player::moveTo(double x, double y) {
	focusPoint.x = x;
	focusPoint.y = y;
}

void Player::add(double x, double y) {
	sprites.push_back(Sprite(x, y, InitialSize, InitialSpeed));
}

void Player::remove(double x, double y) {
	performAtPosition(x, y, [this](int index) {
		sprites[index].die();
	});
}

void Player::makeBigger(double x, double y) {
	performAtPosition(x, y, [this](int index) {
		sprites[index].setSize(sprites[index].getSize() + SizeRate);
	});
}

void Player::makeSmaller(double x, double y) {
	performAtPosition(x, y, [this](int index) {
		sprites[index].setSize(sprites[index].getSize() - SizeRate);
	});
}

void Player::makeFaster(double x, double y) {
	performAtPosition(x, y, [this](int index) {
		sprites[index].setSpeed(sprites[index].getSpeed() + SpeedRate);
	});
}

void Player::makeSlower(double x, double y) {
	performAtPosition(x, y, [this](int index) {
		sprites[index].setSpeed(sprites[index].getSpeed() - SpeedRate);
	});
}

void Player::updateState() {
	std::vector<Sprite> alive;
	for (auto& sprite: sprites) {
		if (sprite.isAlive()) {
			alive.push_back(std::move(sprite));
		}
	}
	sprites = std::move(alive);
	for (size_t i = 0; i < sprites.size(); ++i) {
		computeMovement((int) i, sprites);
	}
}

void Player::computeMovement(int curIndex, std::vector<Sprite>& sprites) {
	double dx = (focusPoint.x - sprites[curIndex].getX());
	double dy = (focusPoint.y - sprites[curIndex].getY());
	double dist = sqrt(dx*dx + dy*dy);
	if (abs(dist) < ErrorEpsilon) {
		dx = 0;
		dy = 0;
	} else {
		dx = dx/dist * sprites[curIndex].getSpeed();
		dy = dy/dist * sprites[curIndex].getSpeed();
	}
	//std::cout << "[" << dx << ", " << dy << "]" << std::endl;
	for(size_t i = 0; i < sprites.size(); ++i) {
		if (curIndex == (int)i) continue;
		double dist = sprites[curIndex].getDistanceTo(sprites[i]);
		double length = sprites[curIndex].getSize()/2 + sprites[i].getSize()/2;
		if (dist > length) continue;
		double sx = sprites[curIndex].getX() - sprites[i].getX();
		double sy = sprites[curIndex].getY() - sprites[i].getY();
		double norm = sqrt(sx*sx + sy*sy);
		if(abs(norm) < ErrorEpsilon) norm = 1;
		sx /= norm;
		sy /= norm;
		double overlapRatio = (length - dist) / sprites[curIndex].getSize();
		double rate = (overlapRatio / OverlapToleration) * sprites[curIndex].getSpeed() * SeperationRate;
		sx *= rate;
		sy *= rate;
		dx += sx;
		dy += sy;
	}
	sprites[curIndex].setPosition(sprites[curIndex].getX() + dx, sprites[curIndex].getY() + dy);
}


int Player::getIndexOfSpriteAtPosition(double x, double y) {
	for (size_t i = 0; i < sprites.size(); ++i) {
		if (sprites[i].contains(x, y)) return static_cast<int>(i);
	}
	return IndexNotFound;
}

void Player::performAtPosition(double x, double y, std::function<void(int)> toPerform) {
	int index = getIndexOfSpriteAtPosition(x, y);
	if (index == IndexNotFound) {
		return;
	}
	toPerform(index);
}

const std::vector<Sprite>& Player::getSprites() {
	return sprites;
}

Player::Player(Player&& temp):
	sprites(std::move(temp.sprites)),
	focusPoint(temp.focusPoint)
	{
		temp.focusPoint.x = 0;
		temp.focusPoint.y = 0;
	}

Player& Player::operator= (Player&& temp) {
	sprites = std::move(temp.sprites);
	focusPoint = temp.focusPoint;
	temp.focusPoint.x = 0;
	temp.focusPoint.y = 0;
	return *this;
}

Player::~Player() {}

}
