#include "simple_logger.h"
#include "testentity.h"

typedef struct {
    Entity* entity_list;
    Uint32 entity_max;
} EntityManager;

static EntityManager _entity_manager = { 0 }; // Initialize a LOCAL global entity manager

void entity_system_initialize(Uint32 max) {
    if (_entity_manager.entity_list) {
        slog("Cannot have two instances of an entity manager; one is already active");
        return;
    }
    if (max == 0) {
        slog("Cannot allocate 0 entities");
        return;
    }

    _entity_manager.entity_list = (Entity*)gfc_allocate_array(sizeof(Entity), max);
    if (!_entity_manager.entity_list) {
        slog("Failed to allocate global entity list");  
        return;
    }

    _entity_manager.entity_max = max;
}

void entity_system_close() {
    entity_clear_all(NULL);
    if (_entity_manager.entity_list) {
        free(_entity_manager.entity_list);
    }
    memset(&_entity_manager, 0, sizeof(EntityManager));
}

void entity_clear_all(Entity* ignore) {
    if (!ignore) {
        return;
    }

    for (int i = 0; i < _entity_manager.entity_max; i++) {
        if (&_entity_manager.entity_list[i] == ignore) {
            continue;
        }
        if (!_entity_manager.entity_list[i]._inuse) {
            continue;
        }
        entity_free(&_entity_manager.entity_list[i]);
    }
}

Entity* entity_new() {
    for (int i = 0; i < _entity_manager.entity_max; i++) {
        if (!_entity_manager.entity_list[i]._inuse) {
            memset(&_entity_manager.entity_list[i], 0, sizeof(Entity));
            _entity_manager.entity_list[i]._inuse = 1;
            return &_entity_manager.entity_list[i];
        }
    }
    slog("No more available entities");
    return NULL;
}

void entity_free(Entity* self) {
    if (!self) {
        return;
    }
    gf2d_sprite_free(self->sprite);
    if (self->free) {
        self->free(self->data);
    }
    memset(self, 0, sizeof(Entity));
}

void entity_think(Entity* self) {
    if (!self) {
        return;
    }
    if (self->think) {
        self->think(self);
    }
}

void entity_update(Entity* self) {
    if (!self) {
        return;
    }
    if (self->update) {
        self->update(self);
    }
}

void entity_draw(Entity* self) {
    if (!self) {
        return;
    }
    if (self->sprite) {
        gf2d_sprite_render(
            self->sprite,
            self->position,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            (Uint32)self->frame
        );
    }
}

void entity_system_think() {
    for (int i = 0; i < _entity_manager.entity_max; i++) {
        if (_entity_manager.entity_list[i]._inuse) {
            entity_think(&_entity_manager.entity_list[i]);
        }
    }
}

void entity_system_update() {
    for (int i = 0; i < _entity_manager.entity_max; i++) {
        if (_entity_manager.entity_list[i]._inuse) {
            entity_update(&_entity_manager.entity_list[i]);
        }
    }
}

void entity_system_draw() {
    for (int i = 0; i < _entity_manager.entity_max; i++) {
        if (_entity_manager.entity_list[i]._inuse) {
            entity_draw(&_entity_manager.entity_list[i]);
        }
    }
}
