#pragma once

enum class SystemId : char {
    GraphicsSystemId, MenuSystemId,MusicSystemId,NetworkSystemId,PhysicsSystemId,SoundSystemId,SpawnerSystemId,
};


enum class SoundType : char {

    ShootingSound, RunnungSound, CollisionSound, DeathSound

};

enum class ObjectType : char {
    Tank, Bullet, Turret ,Map ,Banner, Button,
};
