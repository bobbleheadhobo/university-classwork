#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "mbr.h"
#include "ext4.h"
#include "ntfs.h"

void is_ntfs(FILE *fp) {
    char oem[9]; // 8 characters + 1 for null terminator
    fseek(fp, 3, SEEK_SET);
    if (fread(oem, sizeof(char), 8, fp) != 8) {
        printf("ERROR READING IN OEM ID\n");
    }
    oem[8] = '\0'; // Null-terminate the string

    printf("OEM: %s\n", oem);

    // Check if it's NTFS
    if (strncmp(oem, "NTFS    ", 8) == 0) {
        printf("This is an NTFS file system.\n");
    } else {
        printf("This is not an NTFS file system.\n");
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; 
    }

    struct NTFS_LAYOUT ntfs;
    FILE *fp;

    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        printf("FAILED TO OPEN FILE\n");
        fclose(fp);
        return 1;
    }

    is_ntfs(fp);

    fseek(fp, 512, SEEK_SET);

    if(fread(&ntfs, sizeof(struct NTFS_LAYOUT), 1, fp) != 1){
        printf("ERROR READING IN SUPERBLOCK\n");
        return 1;
    }

    printf("sector size %x\n", ntfs.sector_size);
    printf("sectors per track %x\n", ntfs.sectors_per_track);
    
    fclose(fp);
    return 0;
}

