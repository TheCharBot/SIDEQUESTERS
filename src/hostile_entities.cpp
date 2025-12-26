#include "hostile_entities.hpp"

Enemy_forest_scourge::Enemy_forest_scourge()
{
    
}

Enemy_forest_scourge::~Enemy_forest_scourge()
{
    if(tex.id != 0){
        UnloadTexture(tex);
    }
}

void Enemy_forest_scourge::load()
{
}

void Enemy_forest_scourge::update()
{
}

void Enemy_forest_scourge::draw()
{
}
