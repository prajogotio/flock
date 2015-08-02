#ifndef _FLOCK_SPRITE_H
#define _FLOCK_SPRITE_H


namespace flock{

class Sprite {
public:
	Sprite(double x, double y, double size, double speed);
	void setPosition(double x, double y);
	void setSize(double size);
	void setSpeed(double speed);
	double getX() const;
	double getY() const;
	double getSize() const;
	double getSpeed() const;
	bool contains(double x, double y) const;
	void die();
	bool isAlive() const;
	double getDistanceTo(const Sprite& other) const;


	Sprite(Sprite&&);
	Sprite& operator=(Sprite&&);

	Sprite& operator= (const Sprite&) =delete;
	Sprite(const Sprite&) =delete;

	~Sprite();
private:
	double x;
	double y;
	double size;
	double speed;
	bool alive;
};


}

#endif