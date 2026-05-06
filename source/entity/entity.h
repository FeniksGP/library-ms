#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
	public:
		unsigned int *id;
		
		Entity();
		virtual ~Entity();

		virtual std::string toRaw();
		virtual std::string raw() = 0;
		virtual void set(std::string raw) = 0;
};

#endif
