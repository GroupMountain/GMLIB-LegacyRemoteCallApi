#include "Global.h"
#include "ll/api/event/Cancellable.h"

class HandleRequestActionBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player*                             mPlayer{};
    ItemStackRequestAction& mRequestAction;

public:
    HandleRequestActionBeforeEvent(Player* player, ItemStackRequestAction& requestAction);

    Player* self() const;

    ItemStackRequestAction& getRequestAction() const;
};

class HandleRequestActionAfterEvent final : public ll::event::Event {
private:
    Player*                    mPlayer;
    ItemStackRequestAction& mRequestAction;

public:
    HandleRequestActionAfterEvent(Player* player, ItemStackRequestAction& requestAction);

    Player* self() const;

    ItemStackRequestAction& getRequestAction() const;
};