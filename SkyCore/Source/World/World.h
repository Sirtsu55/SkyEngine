#pragma once


//For entity component system
namespace sky
{

	class World
	{

		World();
		~World();

		World(World&) = delete;
		World& operator=(World&) = delete;

	private:
	};

}