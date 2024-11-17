#ifndef __K_LAYOUT_MAPPINGS_H__
#define __K_LAYOUT_MAPPINGS_H__

#define MAX_LAYOT_MAP_TABLE_ENTRY_NAME (0x20ul)

enum LayoutMapping
{
  LAYOUT_MAPPING_QWERTY = 0,
  LAYOUT_MAPPING_DVORAK = 1,
  LAYOUT_MAPPING_AZERTY = 2
};

struct LayoutMapTableEntry
{
  char map_name[MAX_LAYOT_MAP_TABLE_ENTRY_NAME];
  enum LayoutMapping mapping_value;
};

#endif // __K_LAYOUT_MAPPINGS_H__
