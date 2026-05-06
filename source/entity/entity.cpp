#include "entity.h"

Entity::Entity()
{
	id = new unsigned int;
	*id = 0;
}
Entity::~Entity()
{
	delete id;
}
std::string Entity::toRaw()
{
	return "";
}