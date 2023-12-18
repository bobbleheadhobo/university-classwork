#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mbr.h"

void main(){
    MASTER_BOOT_RECORD MY_MBR;

    int fp;

    fp = open("sda1.out", O_RDONLY);
    if(fp == 0) 
        printf("Broken\n");

    read(fp, &MY_MBR, sizeof(MASTER_BOOT_RECORD));

    printf("The MBR Signiture is %x\n", MY_MBR.Signature);
}
