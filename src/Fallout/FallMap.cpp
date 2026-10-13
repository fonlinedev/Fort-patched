#include "FallMap.h"
#include "FallProto.h"
#include "../FORT.h"
#include <filesystem>
#include <stdexcept>

const std::string ProtoTypeNames[6] = { "Items", "Critters", "Scenery", "Walls", "Tiles", "Misc" };

std::vector<std::vector<std::string>> ProtoLsts;
bool LstsReady = false;
uint32_t MapVer = 0;

FallMapTile_t::FallMapTile_t(ByteReader* reader)
{
	RoofId = reader->u16();
	TileId = reader->u16();
}

void skip_scripts(ByteReader* reader)
{
	for (size_t script_section = 0; script_section < 5; script_section++) 
	{
		uint32_t script_section_count = reader->u32();
		if (script_section_count > 0) 
		{
			uint32_t loop = script_section_count;
			if (script_section_count % 16 > 0) 
			{
				loop += 16 - script_section_count % 16;
			}

			uint32_t check = 0;
			for (size_t j = 0; j < loop; j++) 
			{
				int32_t pid = reader->i32();
				reader->i32();

				pid = (pid & 0xff000000) >> 24;

				switch (pid)
				{
				case 0:
					break;
				case 1:
					reader->u32();
					reader->u32();
					break;
				case 2:
					reader->u32();
					break;
				case 3:
				case 4:
					break;
				default:
					printf(
						"Unknown script PID=%d section=%zu entry=%zu "
						"count=%u loop=%u\n",
						pid,
						script_section,
						j,
						script_section_count,
						loop
					);

					break;
				}
				for (uint8_t i = 0; i < 14; i++)
				{
					reader->u32();
				}

				if ((j % 16) == 15) 
				{
					uint32_t cur_check = reader->u32();
					check += cur_check;
					reader->u32();
				}
			}
		}
	}
}

void SetupProtoLsts()
{
	ProtoLsts.resize(6);
	for (int i = 0; i < 6; i++)
	{
		std::string currString;
		std::filesystem::path path = progSettings.falloutPath + "/proto/" + ProtoTypeNames[i] + "/" + ProtoTypeNames[i] + ".LST";
		std::ifstream input(path);
		if (input.is_open())
		{
			while (getline(input, currString))
			{
				ProtoLsts[i].push_back(currString);
			}
		}
		input.close();
	}
}

FallMapCritObject_t::FallMapCritObject_t(ByteReader* reader)
{
	PlayerReact = reader->u32();
	CurrMP = reader->u32();
	CombatResult = reader->u32();
	DmgLastTurn = reader->u32();
	AiPack = reader->i32();
	GroupId = reader->u32();
	Enemy = reader->u32();
	CurrHP = reader->u32();
	CurrRAD = reader->u32();
	CurrPoison = reader->u32();
}

FallMapAmmoObject_t::FallMapAmmoObject_t(ByteReader* reader)
{
	CurrAmmo = reader->u32();
}

FallMapKeyObject_t::FallMapKeyObject_t(ByteReader* reader)
{
	KeyCode = reader->u32();
}

FallMapMiscObject_t::FallMapMiscObject_t(ByteReader* reader)
{
	Charges = reader->u32();
}

FallMapWeapObject_t::FallMapWeapObject_t(ByteReader* reader)
{
	AmmoCount = reader->u32();
	AmmoPid = reader->i32();
}

FallMapLadderObject_t::FallMapLadderObject_t(ByteReader* reader)
{
	DestHex = reader->u32();
	if (MapVer == 20)
	{
		DestMap = reader->u32();
	}
}

FallMapStairsObject_t::FallMapStairsObject_t(ByteReader* reader)
{
	DestHex = reader->u32();
	DestMap = reader->u32();
}

FallMapDoorObject_t::FallMapDoorObject_t(ByteReader* reader)
{
	WalkThru = reader->u32();
}

FallMapElevObject_t::FallMapElevObject_t(ByteReader* reader)
{
	ElevType = reader->u32();
	ElevLevel = reader->u32();
}

FallMapGridObject_t::FallMapGridObject_t(ByteReader* reader)
{
	ToMapId = reader->u32();
	ChosPos = reader->u32();
	MapElev = reader->u32();
	ChosDir = reader->u32();
}

FallMapObject_t::FallMapObject_t(ByteReader* reader)
{
	reader->u32();
	ObjectPos = reader->i32();
	reader->u32();
	reader->u32();
	reader->u32();
	reader->u32();
	FrameNum = reader->u32();
	Dir = reader->u32();
	FIDType = reader->u8();
	reader->u8();
	FIDNum = reader->u16();
	Flags = reader->u32();
	MapElev = reader->u32();
	PIDType = reader->u8();
	reader->u8();
	PIDNum = reader->u16();
	CritIndex = reader->u32();
	LightRadius = reader->u32();
	LightIntense = reader->u32();
	OutlineColor = reader->u32();
	reader->u32();
	ScriptID = reader->i32();
	InvenSize = reader->u32();
	CritInvenSlots = reader->u32();
	reader->u32();
	reader->u32();

	printf(
		"Object header: ObjectPos=%d PIDType=%u PIDNum=%u "
		"FIDType=%u FIDNum=%u MapElev=%u InvenSize=%u\n",
		ObjectPos,
		static_cast<unsigned>(PIDType),
		static_cast<unsigned>(PIDNum),
		static_cast<unsigned>(FIDType),
		static_cast<unsigned>(FIDNum),
		static_cast<unsigned>(MapElev),
		static_cast<unsigned>(InvenSize)
	);

	if (PIDType >= ProtoLsts.size())
	{
		printf(
			"Invalid PIDType=%u PIDNum=%u ObjectPos=%d\n",
			static_cast<unsigned>(PIDType),
			static_cast<unsigned>(PIDNum),
			ObjectPos
		);

		throw std::runtime_error("Invalid PIDType: MAP parsing stopped");
	}

	if (PIDNum == 0 || PIDNum > ProtoLsts[PIDType].size())
	{
		printf(
			"Invalid PIDNum=%u PIDType=%u ObjectPos=%d\n",
			static_cast<unsigned>(PIDNum),
			static_cast<unsigned>(PIDType),
			ObjectPos
		);

		throw std::runtime_error("Invalid PIDNum: MAP parsing stopped");
	}

	if (PIDType == PROTO_CRITTER)
	{
		CritData = new FallMapCritObject_t(reader);
	}

	if (PIDType == PROTO_ITEM)
	{
		FallProto_t* file = nullptr;
		ByteReader* protoReader = new ByteReader;
		std::filesystem::path path = progSettings.falloutPath + "/proto/" + ProtoTypeNames[PIDType] + "/" + ProtoLsts[PIDType][PIDNum - 1];
		if (!protoReader->Reset(path.string(), ByteReader::BigEndian)) return;
		file = new FallProto_t(protoReader);
		file->Filename = ProtoLsts[PIDType][PIDNum - 1];
		protoReader->Close();
		delete protoReader;

		if (file->ItemPro->AmmoData != nullptr)
		{
			AmmoData = new FallMapAmmoObject_t(reader);
		}

		if (file->ItemPro->KeyData != nullptr)
		{
			KeyData = new FallMapKeyObject_t(reader);
		}

		if (file->ItemPro->MiscData != nullptr)
		{
			MiscData = new FallMapMiscObject_t(reader);
		}

		if (file->ItemPro->WeapData != nullptr)
		{
			WeapData = new FallMapWeapObject_t(reader);
		}

		delete file;
	}

	if (PIDType == PROTO_SCENERY)
	{
		FallProto_t* file = nullptr;
		ByteReader* protoReader = new ByteReader;
		std::filesystem::path path = progSettings.falloutPath + "/proto/" + ProtoTypeNames[PIDType] + "/" + ProtoLsts[PIDType][PIDNum - 1];
		if (!protoReader->Reset(path.string(), ByteReader::BigEndian)) return;
		file = new FallProto_t(protoReader);
		file->Filename = ProtoLsts[PIDType][PIDNum - 1];
		protoReader->Close();
		delete protoReader;

		if (file->ScenPro->LadderData != nullptr)
		{
			LadderData = new FallMapLadderObject_t(reader);
		}

		if (file->ScenPro->DoorData != nullptr)
		{
			DoorData = new FallMapDoorObject_t(reader);
		}

		if (file->ScenPro->StairData != nullptr)
		{
			StairsData = new FallMapStairsObject_t(reader);
		}

		if (file->ScenPro->ElevData != nullptr)
		{
			ElevData = new FallMapElevObject_t(reader);
		}

		delete file;
	}

	if (PIDType == PROTO_MISC)
	{
		if (PIDNum >= 16 && PIDNum <= 23)
		{
			GridData = new FallMapGridObject_t(reader);
		}
	}
}

static void ReadObjectWithInventory(
	ByteReader* reader,
	std::vector<FallMapObject_t>& objects)
{
	FallMapObject_t obj(reader);

	if (obj.InvenSize > 1000)
	{
		throw std::runtime_error("Invalid inventory size: MAP parsing stopped");
	}

	for (size_t i = 0; i < obj.InvenSize; ++i)
	{
		reader->u32(); // Inventory amount
		ReadObjectWithInventory(reader, objects);
	}

	objects.push_back(obj);
}

FallMap_t::FallMap_t(ByteReader* reader)
{
	Version = reader->u32();
	MapVer = Version;
	if (!LstsReady)
	{
		SetupProtoLsts();
		LstsReady = true;
	}
	MapName = reader->string(16);
	DefChosPos = reader->i32();
	DefChosElv = reader->i32();
	DefChosDir = reader->i32();
	LVarsNum = reader->i32();
	ScriptId = reader->i32();
	MapFlags = reader->i32();
	MapDark = reader->i32();
	GVarsNum = reader->i32();
	MapId = reader->i32();
	EpochTime = reader->u32();

	for (int32_t i = 0; i < LVarsNum; i++)
	{
		LVars.push_back(reader->i32());
	}

	for (int32_t i = 0; i < GVarsNum; i++)
	{
		GVars.push_back(reader->i32());
	}

	for (uint8_t i = 0; i < 44; i++)
	{
		reader->i32();
	}

	int tileLen = 10000;
	int elevation = 1;
	switch (MapFlags & 0xE)
	{
	case 0x0c:
		tileLen = 10000;
		elevation = 1;
		break;
	case 0x08:
		tileLen = 20000;
		elevation = 2;
		break;
	case 0x00:
		tileLen = 30000;
		elevation = 3;
		break;
	}

	for (int i = 0; i < tileLen; i++)
	{
		FallMapTile_t currTile(reader);
		Tiles.push_back(currTile);
	}

	skip_scripts(reader);

	TotalObjects = reader->u32();

	printf(
		"Map objects: TotalObjects=%u, elevations=%d, MapFlags=0x%X\n",
		TotalObjects,
		elevation,
		static_cast<unsigned int>(MapFlags)
	);

	uint64_t totalElevationObjects = 0;

	for (size_t elev = 0; elev < static_cast<size_t>(elevation); elev++)
	{
		uint32_t objectsOnElevation = reader->u32();

		totalElevationObjects += objectsOnElevation;

		printf(
			"Elevation %zu: objectsOnElevation=%u, cumulative=%llu\n",
			elev,
			objectsOnElevation,
			static_cast<unsigned long long>(totalElevationObjects)
		);

		for (size_t j = 0; j < objectsOnElevation; j++)
		{
			ReadObjectWithInventory(reader, Objects);
		}
	}
}