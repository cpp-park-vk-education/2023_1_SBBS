#include "Component.h"

class ShootComponent : public Component {
public:

	ShootComponent() {};

	ShootComponent(double cooldown) : cooldown_(cooldown) {};

	void setCooldown(const double& cd) { cooldown_ = cd; };

	double getCooldown() { return cooldown_; };

	void setBulletType(const int type) { type_ = type; };

	int getBulletType() { return type_; };

private:
	int type_;
	double cooldown_;
};