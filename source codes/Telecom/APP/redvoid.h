#ifndef __REDVOID_H__
#define __REDVOID_H__

#define VOID_LEFT 1  // Detected obstacle on the left
#define VOID_RIGHT 2 // Detected obstacle on the right
#define VOID_BOTH 3  // Detected obstacles on both sides
#define VOID_NONE 0  // No obstacles detected

void VoidRun(void);
char GetVoidStatus(void);

#endif

