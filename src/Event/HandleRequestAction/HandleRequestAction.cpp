#include "HandleRequestAction.h"
#include "Global.h"


HandleRequestActionBeforeEvent::HandleRequestActionBeforeEvent(
    Player*                             player,
    ItemStackRequestAction& requestAction
)
: mPlayer(player),
  mRequestAction(requestAction) {}

Player* HandleRequestActionBeforeEvent::self() const { return mPlayer; }

ItemStackRequestAction& HandleRequestActionBeforeEvent::getRequestAction() const { return mRequestAction; }

HandleRequestActionAfterEvent::HandleRequestActionAfterEvent(
    Player*                             player,
    ItemStackRequestAction& requestAction
)
: mPlayer(player),
  mRequestAction(requestAction) {}

Player* HandleRequestActionAfterEvent::self() const { return mPlayer; }

ItemStackRequestAction& HandleRequestActionAfterEvent::getRequestAction() const { return mRequestAction; }


LL_AUTO_TYPE_INSTANCE_HOOK(
    HandleRequestActionHook,
    HookPriority::Normal,
    ItemStackRequestActionHandler,
    "?handleRequestAction@ItemStackRequestActionHandler@@QEAA?AW4ItemStackNetResult@@AEBVItemStackRequestAction@@@Z",
    void,
    ItemStackRequestAction& requestAction
) {
    auto beforeEvent = HandleRequestActionBeforeEvent(((Player*)(*(__int64*)this)), requestAction);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    ll::event::EventBus::getInstance().publish(HandleRequestActionAfterEvent(((Player*)(*(__int64*)this)), requestAction));
    return origin(requestAction);
}