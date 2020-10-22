#include <cmath>
#include "Spinner.h"

#define PI 3.1415926535897932385f
#define DISPLACEMENT_MAG 110

#define SPIN_TIME 2
#define BASE_ROTATION_COUNT 1 

using namespace std;
using namespace cocos2d;

Spinner* Spinner::create(const std::string& file_name, const std::vector<Prize*> prizes) {
	return new Spinner(file_name, prizes);
};

bool Spinner::init() {

	float total = 0;
	int i = 0;

	// probability is weighted based on the relative value of each item
	const Quaternion eighth_rot(Vec3::UNIT_Z, PI / 4);
	Quaternion running_rot = Quaternion(Vec3::UNIT_Z, PI / 8);
	const Vec3 displacement_vec(0, DISPLACEMENT_MAG, 0);

	// add up the totals of the prizes and position each of them
	for (Prize* prize : prizes) {
		total += prize->getRelativeProbability();
		this->addChild(prize, 1);
		makeChildOfAndCenter(prize, this, 1);
		probabilityLevels[i++] = prize->getRelativeProbability();
		
		prize->setRotationQuat(running_rot);
		Vec3 rotated_displacement = running_rot * displacement_vec;
		prize->setPosition(prize->getPosition() + Vec2(rotated_displacement.x, rotated_displacement.y));
		running_rot = eighth_rot * running_rot;
	}

	float total_sum_to_one = 0;
	for (int i = 0; i < SPINNER_SECTIONS; i++) {
		probabilityLevels[i] /= total;
		float individual_probability = probabilityLevels[i];
		probabilityLevels[i] += total_sum_to_one;
		total_sum_to_one += individual_probability;
	}

	CCASSERT(abs(probabilityLevels[SPINNER_SECTIONS - 1] - 1) < .000001f, "Probabilities' totals did not sum to 1");
	this->scheduleUpdate();
	return true;
}

void Spinner::spin(cocos2d::Ref* ref){
	float random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	int i = 0;
	while (probabilityLevels[i++] < random) {}

	float rotation = i * PI / 4;
	rotation += BASE_ROTATION_COUNT * 2 * PI;
	float w_naught = (2 * rotation) / SPIN_TIME;
	float a = -w_naught / SPIN_TIME;
	
	Quaternion init_rot = this->getRotationQuat();

	this->rot_animator = new PropertyAnimator<Quaternion>(
		[&](Quaternion set) -> void {
			this->setRotationQuat(set);
		},
		[&, w_naught, init_rot, a](float elapsed_s) -> Quaternion {
			float theta = (a * (elapsed_s * elapsed_s) / 2) + w_naught * elapsed_s;
			return Quaternion(Vec3::UNIT_Z, theta) * init_rot; 
		}, 
			SPIN_TIME);

}

void Spinner::update(float delta){
	if (rot_animator) {
		rot_animator->update(delta);
		if (rot_animator->isComplete()) {
			delete rot_animator;
			rot_animator = nullptr;
		}
	}
}


Spinner::Spinner(const string& file_name, const std::vector<Prize*>& prizes) : Sprite(), prizes(prizes), rot_animator(nullptr) {
	CCASSERT(prizes.size() == SPINNER_SECTIONS, "Invalid prize count for Spinner type");
	
	// call into the Sprite base class' init function with the file name
	initWithFile(file_name);
	makeChildOfAndCenter(Sprite::create("wheel_border.png"), this, 1);
	// call into this class' init implementation
	init();
}