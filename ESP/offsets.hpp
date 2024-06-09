#pragma once

namespace offsets {
    namespace world {
        constexpr auto world = 0x4169C58;
        constexpr auto near_entity_table = 0xF48;
        constexpr auto near_entity_table_size = near_entity_table + 0x8;
        constexpr auto far_entity_table = 0x1090;
        constexpr auto far_entity_table_size = far_entity_table + 0x8;
        constexpr auto bullet_table = 0xE00;
        constexpr auto bullet_table_size = bullet_table + 0x8;
        constexpr auto local_player = 0x2960;
        constexpr auto camera = 0x1B8;
    }

    namespace camera {
        constexpr auto view_projection = 0xD0;
        constexpr auto view_matrix = 0x8;
        constexpr auto view_port_matrix = 0x58;
    }

    namespace human_type {
        constexpr auto object_name = 0x70;
        constexpr auto category_name = 0xA8;
    }

    namespace weapon {
        constexpr auto muzzle_count = 0x6E4;
        constexpr auto weapon_info_size = 0xE0;
        constexpr auto weapon_index = 0x6D0;
        constexpr auto weapon_info_table = 0x6D8;
    }

    namespace magazine {
        constexpr auto magazine_type = 0x180;
        constexpr auto ammo_count = 0x6DC;
    }

    namespace human {
        constexpr auto visual_state = 0x1D0;
        constexpr auto human_type = 0x180;
        constexpr auto lod_shape = 0x208;
    }

    namespace anim_class {
        constexpr auto matrix_array = 0xBF0;
    }

    namespace inventory_item {
        constexpr auto item_inventory = 0x680;
    }

    namespace dayz_infected {
        constexpr auto skeleton = 0x6A0;
    }

    namespace dayz_player {
        constexpr auto skeleton = 0x830;
        constexpr auto network_id = 0x70C;
        constexpr auto inventory = 0x680;
    }

    namespace visual_state {
        constexpr auto inverse_transform = 0xA4;
        constexpr auto transform = 0x8;
    }

    namespace dayz_player_inventory {
        constexpr auto hands = 0x1B0;
    }

    namespace weapon_inventory {
        constexpr auto magazine_ref = 0x150;
    }

    namespace ammo_type {
        constexpr auto init_speed = 0x364;
        constexpr auto air_friction = 0x3B4;
    }

    namespace skeleton {
        constexpr auto anim_class1 = 0x70;
        constexpr auto anim_class2 = 0x28;
    }
}
