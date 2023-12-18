/*
 * @file myfile.c
 * @author Joey Troyer
 * @purpose To read in various files and tell the user info about the file
 * @date 2023-11-21
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <endian.h> // For byte order conversion functions
#include "mbr.h"
#include "ext4.h"
#include "ntfs.h"


// function to check if file is an MBR based on its signature
int is_mbr(FILE *fp){
    MASTER_BOOT_RECORD mbr;

    // read in struct from file
    if(fread(&mbr, sizeof(MASTER_BOOT_RECORD), 1, fp) != 1){
        printf("ERROR READING IN MBR\n");
        return -1;
    }

    // check if signature matches mbr signature
    if(mbr.Signature == 0xaa55){
        printf("MBR SIGNATURE %x\n", mbr.Signature);
        return 1;
    }

    return 0;
}

// check if file is linux type
int is_ext4(FILE *fp){
    struct ext4_super_block ext4;

    // set pointer to after first block in the file
    fseek(fp, 1024, SEEK_SET);

    // read in ext4 superblock
    if(fread(&ext4, sizeof(struct ext4_super_block), 1, fp) != 1){
        printf("ERROR READING IN SUPERBLOCK\n");
        return -1;
    }

    // check if file is ext4 based on magic number
    if(ext4.s_magic == 0xEF53)
        return 1;
    
    return 0;
}

// check if file is ntfs type
int is_ntfs(FILE *fp) {
    char oem[9]; // 8 characters + 1 for null terminator

    // set pointer three bytes in to where the oedm_id starts
    fseek(fp, 3, SEEK_SET);

    // read in the next 8 bytes of the file which is the size of the oem
    if (fread(oem, sizeof(char), 8, fp) != 8) {
        printf("ERROR READING IN OEM ID\n");
        return -1;
    }
    oem[8] = '\0'; // Null-terminate the string

    // Check oem equals the same oem as ntfs files
    if (strncmp(oem, "NTFS    ", 8) == 0)
        return 1;
    
    return 0;
}

// print all the info for ext4 files
void print_ext4(FILE *fp){
    struct ext4_super_block ext4;

    // set the pointer to where the super block starts 
    fseek(fp, 1024, SEEK_SET);

    // read in the info
    if(fread(&ext4, sizeof(struct ext4_super_block), 1, fp) != 1){
        printf("ERROR READING IN SUPERBLOCK\n");
    }

    // print the necessary info of the file
    printf("EXT4 FILE\n");
    printf("INODES %x\n", ext4.s_inodes_count);
    printf("BLOCKS %x\n", ext4.s_blocks_count_lo);
    printf("MAGIC NUMBER %x\n", ext4.s_magic);
    printf("LAST MOUNTED %s\n", ext4.s_last_mounted);
    printf("VOLUME NAME %s\n", ext4.s_volume_name);

    // Print UUID char array
    printf("VOLUME ID ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", ext4.s_uuid[i]);
    }
    printf("\n");

}

void print_ntfs(FILE *fp){
    struct NTFS_LAYOUT ntfs;

    // read in the struct from the file
    if(fread(&ntfs, sizeof(struct NTFS_LAYOUT), 1, fp) != 1){
        printf("ERROR READING IN NTFS LAYOUT\n");
        return;
    }

    // print the files info
    printf("NTFS FILE\n");
    printf("OEM ID %s\n", ntfs.oem_id);
    printf("SECTOR SIZE 0x%x\n", ntfs.bytes_per_sector);
    printf("SECTORS PER TRACK 0x%x\n", ntfs.sectors_per_track);
    printf("HEADS 0x%x\n", ntfs.number_of_heads);
    printf("OS 0x%x\n", ntfs.os);
    printf("TOTAL SECTORS 0x%llx == %lld\n", ntfs.total_sectors, ntfs.total_sectors);
    printf("STARTING CLUSTER 0x%llx == %lld\n", ntfs.mft_starting_cluster_number, ntfs.mft_starting_cluster_number);
    printf("MIRR STARTING CLUSTER 0x%llx == %lld\n", ntfs.mftmirr_starting_cluster_number, ntfs.mftmirr_starting_cluster_number);
    printf("SERIAL NUMBER 0x%llx\n", ntfs.volume_serial_number);
}


// determines what kind of file is given and prints in relevant info
int main(int argc, char *argv[]) {
    // makes sure user enters a file
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; 
    }

    FILE *fp;

    // open the file in read and bytes
    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        printf("FAILED TO OPEN FILE\n");
        return 1;
    }


    // Check for MBR
    if (is_mbr(fp)) {
        // Check for NTFS
        fseek(fp, 0, SEEK_SET); // Reset file pointer

        if (is_ntfs(fp)) {

            fseek(fp, 0, SEEK_SET); // Reset file pointer
            print_ntfs(fp);
        }
        else {
            printf("UNKOWN MBR FILE TYPE");
        }
    }
    // Check for EXT4
    else if (is_ext4(fp)) {
                fseek(fp, 0, SEEK_SET); // Reset file pointer
                print_ext4(fp);
            }
    else {
        printf("UNKOWN FILE TYPE\n");
    }

}