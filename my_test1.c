/*
CS525: Advanced Database Organization
Fall 2021 | Group 22
Isa Muradli           (imuradli@hawk.iit.edu)       (Section 01)
Andrew Petravicius    (apetravicius@hawk.iit.edu)   (Section 01)
Christopher Sherman   (csherman1@hawk.iit.edu)      (Section 02)
*/

#include "dberror.h"
#include "storage_mgr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (void) {
  SM_FileHandle fHandle;       // file handle for tests
  SM_PageHandle pHandle1, pHandle2;      // two page handles for testing read and write
  char buf1[PAGE_SIZE];        // buffer to write from in tests
  char buf2[PAGE_SIZE+1];      // buffer to read to (extra for null terminate)
  int outputsEqual;            // boolean for determining if write = read
  char* fileName = "my_test_create.bin";

  printf("Test Start\n\n");

  // create a page file
  createPageFile(fileName);
  printf("File Created!\n");

  // test openPageFile, print fHandle info
  openPageFile(fileName, &fHandle);
  printf("File Name: %s\n", fHandle.fileName);
  printf("Current Page Position: %d\n", fHandle.curPagePos);
  printf("Total Number of Pages: %d\n", fHandle.totalNumPages);
  printf("MgmtInfo Pointer: %p\n", fHandle.mgmtInfo);

  // make every character in bu1 'A'
  for(int i = 0; i < PAGE_SIZE; i++){
      buf1[i] = 'A';
  }

  // terminate buf2 in null char (for printf)
  buf2[PAGE_SIZE] = '\0';

  // assign the buffers to the page handles
  pHandle1 = buf1;
  pHandle2 = buf2;

  // test writeblock
  printf("\nWriting into the block!!\n");
  writeBlock(0, &fHandle, pHandle1);

  //test readblock, read what was written
  printf("\nReading first block from file\n");
  readBlock(0, &fHandle, pHandle2);

  outputsEqual = 1;
  for(int i = 0; i < PAGE_SIZE; i++) {
    if(pHandle1[i] != pHandle2[i]) {
      outputsEqual = 0;
    }
  }

  if(outputsEqual == 1) {
    printf("SUCCESS: Read Block = Write Block\n");
  }
  else {
    printf("FAILURE: Read Block != Write Block\n");
  }

  // print out result from read
  printf("\n%s\n", pHandle2);

  printf("\nClosing Page File\n");
  closePageFile(&fHandle);
  printf("File Closed!\n");

  //destroyPageFile(fileName);
  //printf("File is destroyed!\n");

  printf("\nTest Over\n");
  return 0;
}
