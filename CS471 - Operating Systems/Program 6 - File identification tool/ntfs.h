#include <linux/types.h>

#pragma pack(1)

struct NTFS_LAYOUT {
    __u8    jump_instruction[3];           // Offset 0x00 - 0x02
    __u8    oem_id[8];                     // Offset 0x02 - 0x0A
    __le16  bytes_per_sector;              // Offset 0x0B - 0x0C
    __u8    sectors_per_cluster;           // Offset 0x0D
    __u8    reserved_0E;                   // Offset 0x0E
    __u8    reserved_0F;                   // Offset 0x0F
    __u8    reserved_10;                   // Offset 0x10
    __u16   reserved_11;                   // Offset 0x11 - 0x12
    __u16   reserved_13;                   // Offset 0x13 - 0x14
    __u8    media_descriptor;              // Offset 0x15
    __u16   reserved_16;                   // Offset 0x16 - 0x17
    __le16  sectors_per_track;             // Offset 0x18 - 0x19
    __le16  number_of_heads;               // Offset 0x1A - 0x1B
    __le32  hidden_sectors;                // Offset 0x1C - 0x1F
    __u32   reserved_20;                   // Offset 0x20 - 0x23
    __le32  os;                            // Offset 0x24 - 0x27
    __u64   total_sectors;                 // Offset 0x28 - 0x2F
    __u64   mft_starting_cluster_number;   // Offset 0x30 - 0x37
    __u64   mftmirr_starting_cluster_number;// Offset 0x38 - 0x3F
    __s8    clusters_per_file_record;      // Offset 0x40
    __u8    reserved_41[3];                // Offset 0x41 - 0x43
    __s8    clusters_per_index_buffer;     // Offset 0x44
    __u8    reserved_45[3];                // Offset 0x45 - 0x47
    __u64   volume_serial_number;          // Offset 0x48 - 0x4F
    __u32   checksum;                      // Offset 0x50 - 0x53
    __u8    bootstrap_code[426];           // Offset 0x54 - 0x1FD
    __le16  end_of_sector_marker;          // Offset 0x1FE - 0x1FF
};

#pragma pop(1)
