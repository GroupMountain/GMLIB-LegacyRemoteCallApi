#pragma once
#include <span>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>

namespace gmlib {

class LegacyRemoteCallApi {

public:
    static std::unique_ptr<LegacyRemoteCallApi>& getInstance();

    LegacyRemoteCallApi(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the plugin is loaded successfully.
    bool load();

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

    // TODO: Implement this method if you need to unload the plugin.
    // /// @return True if the plugin is unloaded successfully.
    // bool unload();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace gmlib
