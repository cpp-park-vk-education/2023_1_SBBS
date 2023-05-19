#include "Component.h"

class ShootComponent : public Component {
public:

	ShootComponent() {};

	ShootComponent(double cooldown) : cooldown_(cooldown) {};

	void setCooldown(const double& cd) { cooldown_ = cd; };

	double getCooldown() { return cooldown_; };

	void setBulletType(const char& type) { type_ = type; };

	char getBulletType() { return type_; };

private:
	char type_;
	double cooldown_;
};