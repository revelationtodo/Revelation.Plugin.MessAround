#include "MessAroundInterface.h"
#include "ICommonWidgetInterface.h"
#include "MessAround.h"
#include "FluDef.h"
#include "FluThemeUtils.h"
#include "FluSettingsVersionBox.h"

MessAroundInterface::MessAroundInterface(IRevelationInterface* intf)
    : m_interface(intf)
{
}

MessAroundInterface::~MessAroundInterface()
{
    delete m_messAround;
}

void MessAroundInterface::Initialize()
{
}

void MessAroundInterface::Uninitialize()
{
}

void MessAroundInterface::HandleBroadcast(BroadcastType broadcastType, const std::any& param /* = std::any() */)
{
    if (broadcastType == BroadcastType::CollectNavigationView)
    {
        AddNavigationView();
    }
    else if (broadcastType == BroadcastType::CollectSettingsItem)
    {
        // AddSettingsItem();
    }
    else if (broadcastType == BroadcastType::ChangeTheme)
    {
        FluTheme theme = std::any_cast<FluTheme>(param);
        FluThemeUtils::getUtils()->setTheme(theme);
    }
}

void MessAroundInterface::AddNavigationView()
{
    auto commonWidgetIntf = m_interface->GetCommonWidgetInterface();
    if (nullptr != commonWidgetIntf)
    {
        m_messAround = new MessAround();
        commonWidgetIntf->AddStackedWidget(m_messAround, QObject::tr("MessAround"), FluAwesomeType::Emoji, Qt::AlignCenter);
    }
}

void MessAroundInterface::AddSettingsItem()
{
    auto        timeMachineItem = new FluSettingsVersionBox;
    timeMachineItem->getTitleLabel()->setText("RevelationPluginSample");
    timeMachineItem->getInfoLabel()->setText("This is a plugin setting sample.");
    timeMachineItem->getVersionLabel()->setText(QString::fromStdString("1.0.0"));

    QIcon icon = FluIconUtils::getFluentIcon(FluAwesomeType::Emoji);
    timeMachineItem->getIconLabel()->setPixmap(icon.pixmap(40, 40));
    timeMachineItem->getIconLabel()->setFixedSize(40, 40);

    m_interface->GetCommonWidgetInterface()->AddSettingsItem(timeMachineItem);
}
