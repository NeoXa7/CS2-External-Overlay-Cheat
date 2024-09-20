//if (Config::Esp::enableEspArmorPointsText)
			//{
			//	char ArmorText[16];
			//	snprintf(ArmorText, sizeof(ArmorText), "Vest : %d", entities->Armor);

			//	// Calculate the position for the health text to be just above the health bar
			//	ImVec2 armorBarTopRight(topRight.x - 6.0f - 5.0f, bottomRight.y - (bottomRight.y - topRight.y));
			//	Vector2 armorTextPos(armorBarTopRight.x - 20.0f, armorBarTopRight.y - 20.0f);
			//	ESP::DrawTextW
			//	(
			//		ArmorText, 
			//		armorTextPos, 
			//		Config::Esp::ArmorBarColor, 
			//		false
			//	);
			//}

//uintptr_t MapNameAddress = Memory::ReadMemory<uintptr_t>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
//Memory::ReadArray<char>(MapNameAddress, MapName, sizeof(MapName));