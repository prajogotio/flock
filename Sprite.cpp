#include "flock.h"
#include <cmath>
namespace flock {

Sprite::Sprite(double x_, double y_, double size_, double speed_):
	x(x_), 
	y(y_),
	size(size_),
	speed(speed_),
	alive(true) 
	{}

void Sprite::setPosition(double newX, double newY) {
	x = newX;
	y = newY;
}

void Sprite::setSize(double newSize) {
	size = newSize;
	if (size < 1) size = 1;
}

void Sprite::setSpeed(double newSpeed) {
	speed = newSpeed;
	if (speed < 1) speed = 1;
}

double Sprite::getX() const {
	return x;
}

double Sprite::getY() const {
	return y;
}

double Sprite::getSize() const {
	return size;
}

double Sprite::getSpeed() const {
	return speed;
}

bool Sprite::contains(double cx, double cy) const {
	return (x - size/2.0 < cx && cx < x + size/2.0 && 
		y - size/2.0 < cy && cy < y + size/2.0);
}

void Sprite::die() {
	alive = false;
}

bool Sprite::isAlive() const {
	return alive;
}

double Sprite::getDistanceTo(const Sprite& other) const {
	double dx = (other.x - x);
	double dy = (other.y - y);
	return sqrt(dx*dx + dy*dy);
}

Sprite::Sprite(Sprite&& temp):x(temp.x), y(temp.y), size(temp.size), speed(temp.speed), alive(temp.alive) {
	temp.x = 0;
	temp.y = 0;
	temp.size = 0;
	temp.speed = 0;
	temp.alive = false;
}

Sprite& Sprite::operator= (Sprite&& temp) {
	x = temp.x;
	y = temp.y;
	size = temp.size;
	speed = temp.speed;
	alive = temp.alive;
	temp.x = 0;
	temp.y = 0;
	temp.size = 0;
	temp.speed = 0;
	temp.alive = false;
	return *this;
}

Sprite::~Sprite() {}

}