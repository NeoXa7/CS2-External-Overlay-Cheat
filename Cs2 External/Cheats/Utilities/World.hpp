#pragma once
#include <unordered_map>
#include <string>

static const std::unordered_map<std::string, std::string> EntityType = {
    {"chicken", "Chicken"},
    {"hostage_entity", "Hostage"}
};

static const std::unordered_map<std::string, std::string> ProjectilesType = {
    {"smokegrenade_projectile", "Smoke Grenade"},
    {"flashbang_projectile", "Flashbang"},
    {"hegrenade_projectile", "HE Grenade"},
    {"molotov_projectile", "Molotov"},
    {"incendiarygrenade_projectile", "Incendiary Grenade"},
    {"decoy_projectile", "Decoy Grenade"}
};

static const std::unordered_map<std::string, std::string> WeaponsType = {
    {"weapon_ak47", "AK-47"},
    {"weapon_m4a1", "M4A1"},
    {"weapon_awp", "AWP"},
    {"weapon_elite", "Elite"},
    {"weapon_famas", "Famas"},
    {"weapon_flashbang", "Flashbang"},
    {"weapon_g3sg1", "G3SG1"},
    {"weapon_galilar", "Galil AR"},
    {"weapon_healthshot", "Health Shot"},
    {"weapon_hegrenade", "HE Grenade"},
    {"weapon_incgrenade", "Incendiary Grenade"},
    {"weapon_m249", "M249"},
    {"weapon_m4a1_silencer", "M4A1-S"},
    {"weapon_mac10", "MAC-10"},
    {"weapon_mag7", "MAG-7"},
    {"weapon_molotov", "Molotov"},
    {"weapon_mp5sd", "MP5-SD"},
    {"weapon_mp7", "MP7"},
    {"weapon_mp9", "MP9"},
    {"weapon_negev", "Negev"},
    {"weapon_nova", "Nova"},
    {"weapon_p90", "P90"},
    {"weapon_sawedoff", "Sawed-Off"},
    {"weapon_scar20", "SCAR-20"},
    {"weapon_sg556", "SG 553"},
    {"weapon_smokegrenade", "Smoke Grenade"},
    {"weapon_ssg08", "SSG 08"},
    {"weapon_tagrenade", "TA Grenade"},
    {"weapon_taser", "Taser"},
    {"weapon_ump45", "UMP-45"},
    {"weapon_xm1014", "XM1014"},
    {"weapon_aug", "AUG"},
    {"weapon_bizon", "PP-Bizon"},
    {"weapon_decoy", "Decoy Grenade"},
    {"weapon_fiveseven", "Five-Seven"},
    {"weapon_hkp2000", "P2000"},
    {"weapon_usp_silencer", "USP-S"},
    {"weapon_p250", "P250"},
    {"weapon_tec9", "Tec-9"},
    {"weapon_cz75a", "CZ75-Auto"},
    {"weapon_deagle", "Desert Eagle"},
    {"weapon_revolver", "R8 Revolver"},
    {"weapon_glock", "Glock-18"}
};


// Function to retrieve item names
std::string GetWeaponType(const std::string& itemIdentifier)
{
    auto it = WeaponsType.find(itemIdentifier);
    if (it != WeaponsType.end())
        return it->second;
    return "<unknown>";
}

std::string GetProjectileType(const std::string& itemIdentifier)
{
    auto it = ProjectilesType.find(itemIdentifier);
    if (it != ProjectilesType.end())
        return it->second;
    return "<unknown>";
}

std::string GetEntityType(const std::string& itemIdentifier)
{
    auto it = EntityType.find(itemIdentifier);
    if (it != EntityType.end())
        return it->second;
    return "<unknown>";
}