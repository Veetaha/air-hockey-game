#include "AirHockeyGame.h"
#include "Ecs/EntityMgr.h"
#include "Ecs/Entity.h"
#include "Ecs/Components/MovementComponent.h"
#include "Ecs/Components/SpriteComponent.h"
#include "TextureMgr.h"


void AirHockeyGame::init(const InitOpts& opts) {
	Super::init(opts);

	auto& entityMgr{ getEntityManager() };
	auto& renderer{ getRenderer() };
	
	auto sampleEntity{ std::make_unique<Entity>() };

	sampleEntity->setComponent<MovementComponent>(Vector2D(500, 0), Vector2D(4, 24));
	
	auto texture{ TextureMgr::createTextureFromFile(renderer, "assets/img/sample.png") };
	sampleEntity->setComponent<SpriteComponent>(
		std::move(texture), 
		Dimensions2D{ 60, 60 }
	);
	
	entityMgr.addEntity(std::move(sampleEntity));

}
