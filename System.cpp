#include "System.h"

int System::Width = GetSystemMetrics(SM_CXSCREEN);
int System::Height = GetSystemMetrics(SM_CYSCREEN);
int System::MouseButtonNumber = GetSystemMetrics(SM_CMOUSEBUTTONS);
int System::NumberofMonitors = GetSystemMetrics(SM_CMONITORS);

