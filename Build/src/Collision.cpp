#include "Collision.h"

GameEngine::Collision::Collision()
{
}

bool GameEngine::Collision::TestAABBAABB(std::shared_ptr<AABB> a, std::shared_ptr<AABB> b)
{
    if (abs(a->center[0] - b->center[0]) > (a->extents[0] + b->extents[0])) return 0;
    if (abs(a->center[1] - b->center[1]) > (a->extents[1] + b->extents[1])) return 0;
    if (abs(a->center[2] - b->center[2]) > (a->extents[2] + b->extents[2])) return 0;
    return 1;
}

void GameEngine::Collision::AddAABB(std::shared_ptr<AABB> a)
{
    collisions.push_back(a);
}

void GameEngine::Collision::CollisionCheck()
{
    if (collisions.size() > 1)
    {
        if (TestAABBAABB(collisions[0], collisions[1]))
        {
            std::cout << "coll";

        }
    }
}
