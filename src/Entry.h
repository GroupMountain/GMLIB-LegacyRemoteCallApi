#pragma once
#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/thread/ThreadPoolExecutor.h>

namespace gmlib {

class LegacyRemoteCallApi {

public:
    static LegacyRemoteCallApi& getInstance();

    LegacyRemoteCallApi() : mSelf(*ll::mod::NativeMod::current()), mThreadPoolExecutor(getSelf().getName()) {}

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

    ll::thread::ThreadPoolExecutor& getThreadPoolExecutor() { return mThreadPoolExecutor; }

private:
    ll::mod::NativeMod&            mSelf;
    ll::thread::ThreadPoolExecutor mThreadPoolExecutor;
};

} // namespace gmlib
