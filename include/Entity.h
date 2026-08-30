#include <array>
class Entity {
public:
	virtual std::array<float, 2> getPosition() const = 0;
	virtual ~Entity() = default;
};
