#include "IExtensionInterface.h"
#include "IRevelationInterface.h"
#include <QLabel>

class MessAround;
class MessAroundInterface : public IExtensionInterface
{
  public:
    MessAroundInterface(IRevelationInterface* intf);
    ~MessAroundInterface();

    virtual void Initialize() override;
    virtual void Uninitialize() override;

    virtual void HandleBroadcast(BroadcastType broadcastType, const std::any& param /* = std::any() */) override;

  private:
    void AddNavigationView();
    void AddSettingsItem();

  private:
    IRevelationInterface* m_interface = nullptr;

    MessAround* m_messAround = nullptr;
};