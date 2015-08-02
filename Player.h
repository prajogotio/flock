#ifndef _FLOCK_PLAYER_H
#define _FLOCK_PLAYER_H

#include "Sprite.h"
#include <vector>
#include <functional>

namespace flock {

class Player {
public:

	Player(double x, double y);
	void moveTo(double x, double y);
	void add(double x, double y);
	void remove(double x, double y);
	void makeBigger(double x, double y);
	void makeSmaller(double x, double y);
	void makeFaster(double x, double y);
	void makeSlower(double x, double y);
	void updateState();
	const std::vector<Sprite>& getSprites();

	Player(const Player&) =delete;
	Player& operator= (const Player&) =delete;

	Player(Player&&);
	Player& operator= (Player&&);

	~Player();
private:

	struct position {
		double x;
		double y;
		position(double x_, double y_):x(x_), y(y_) {}
	};

	static constexpr double InitialSpeed = 0.7;
	static constexpr double InitialSize = 40.0;

	static constexpr int IndexNotFound = -1;

	static constexpr double SizeRate = 1;
	static constexpr double SpeedRate = 0.004;
	static constexpr double ErrorEpsilon = 1e-5;
	static constexpr double SeperationRate = 0.34;
	static constexpr double OverlapToleration = 0.13;

	std::vector<Sprite> sprites;
	position focusPoint;

	int getIndexOfSpriteAtPosition(double x, double y);
	void performAtPosition(double x, double y, std::function<void(int)> toPerform);
	void computeMovement(int index, std::vector<Sprite>& sprites);
};

}

#endif