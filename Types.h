#pragma once

enum class ConnectionType : char { Host, Client,Null };

enum class GameStateId : char {
    MainMenu, HostMenu, ClientMenu, HostPlaying, ClientPlaying, SingleMenu, SinglePlaying
};

enum class SystemId : char {
    GraphicsSystemId, MenuSystemId, MusicSystemId, PhysicsSystemId, SoundSystemId, SpawnerSystemId, PauseSystemId
};


enum class SoundType : char {

    ShootingSound, RunnungSound, CollisionSound, DeathSound

};

enum class ObjectType : char {
    Tank, Bullet, Turret ,Wall,Floor ,Banner, Button, Null, PauseMenu
};
