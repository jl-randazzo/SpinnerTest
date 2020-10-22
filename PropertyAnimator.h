#pragma once
#include <functional>

template <typename T>
class PropertyAnimator {
public:
	PropertyAnimator(std::function<void(T)> property_setter, std::function<T(float)> property_animator, float time_limit)
		: property_setter(property_setter), property_animator(property_animator), elapsed_s(0), complete(false), time_limit(time_limit) { }

	void update(float delta) {
		elapsed_s += delta;
		if (elapsed_s > time_limit) {
			elapsed_s = time_limit;
			complete = true;
		}

		T t = property_animator(elapsed_s);
		property_setter(t);
	}

	bool isComplete() {
		return complete;
	}

private:
	bool complete;
	float elapsed_s;
	const float time_limit;
	const std::function<void(T)> property_setter;
	const std::function<T(float)> property_animator;

};
