#include "IRevelationInterface.h"
#include "MessAroundInterface.h"

DLL_EXPORT IExtensionInterface* ExtensionEntrance(IRevelationInterface* intf)
{
    return new MessAroundInterface(intf);
}