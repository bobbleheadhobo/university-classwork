#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mbr.h"
#include "ext4.h"

void print_ext4(struct ext4_super_block ext4){

    printf("Inodes count: %u\n", ext4.s_inodes_count);
    printf("Blocks count: %u\n", ext4.s_blocks_count_lo);
    printf("magic number: %x\n", ext4.s_magic);
    printf("Last mounted on: %s\n", ext4.s_last_mounted);
    printf("Volume name: %s\n", ext4.s_volume_name);
    printf("Volume ID: %d\n", ext4.s_uuid);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; 
    }

    struct ext4_super_block ext4;
    FILE *fp;

    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        printf("FAILED TO OPEN FILE\n");
        fclose(fp);
        return 1;
    }

    fseek(fp, 1024, SEEK_SET);

    if(fread(&ext4, sizeof(struct ext4_super_block), 1, fp) != 1){
        printf("ERROR READING IN SUPERBLOCK\n");
        fclose(fp);
        return 1;
    }

    print_ext4(ext4);
    
    fclose(fp);
    return 0;
}

