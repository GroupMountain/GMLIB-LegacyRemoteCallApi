#include "Global.h"
using namespace ll::hash_utils;

class LegacyScriptBinaryStreamManager {
private:
    int64                                                           mNextBinaryStreamId = 0;
    std::unordered_map<uint64, std::shared_ptr<GMLIB_BinaryStream>> mBinaryStream;

public:
    uint getNextId() { return mNextBinaryStreamId++; }

    void cretateBinaryStream(uint id) { mBinaryStream[id] = std::make_shared<GMLIB_BinaryStream>(); }

    void removeBinaryStream(uint64 id) { mBinaryStream.erase(id); }

    std::shared_ptr<GMLIB_BinaryStream> getBinaryStream(uint64 id) {
        return mBinaryStream.contains(id) ? mBinaryStream.at(id) : nullptr;
    }

public:
    static LegacyScriptBinaryStreamManager& getInstance() {
        static std::unique_ptr<LegacyScriptBinaryStreamManager> instance;
        if (!instance) instance = std::make_unique<LegacyScriptBinaryStreamManager>();
        return *instance;
    }
};

#define BinaryStreamManager LegacyScriptBinaryStreamManager::getInstance()
#define EXPORTAPI(funcName, type, fuc)                                                                                 \
    RemoteCall::exportAs("GMLIB_BinaryStream_API", funcName, [](uint64 id, type value) -> void {                       \
        auto bs = BinaryStreamManager.getBinaryStream(id);                                                             \
        if (bs != nullptr) fuc;                                                                                        \
    })

template <typename T>
struct Info;
template <typename T, typename R, typename A, typename... AS>
struct Info<R (T::*)(A, AS...)> {
    using ArgT = A;
};
#define EXPORTAPI2(T) EXPORTAPI(#T, Info<decltype(&GMLIB_BinaryStream::T)>::ArgT, bs->T(value))

void Export_BinaryStream_API() {
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "create", []() -> uint64 {
        auto id = BinaryStreamManager.getNextId();
        BinaryStreamManager.cretateBinaryStream(id);
        return id;
    });
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "reset", [](uint64 id) -> void {
        if (BinaryStreamManager.getBinaryStream(id) == nullptr) BinaryStreamManager.cretateBinaryStream(id);
        else BinaryStreamManager.getBinaryStream(id)->reset();
    });
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "sendTo", [](uint64 id, Player* player) -> void {
        if (auto bs = BinaryStreamManager.getBinaryStream(id); bs != nullptr) bs->sendTo(*player);
    });
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "destroy", [](uint64 id) -> void {
        BinaryStreamManager.removeBinaryStream(id);
    });
    EXPORTAPI("writePacketHeader", int, bs->writePacketHeader((MinecraftPacketIds)value));
    EXPORTAPI("writeUuid", std::string const&, bs->writeUuid(mce::UUID::fromString(value)));
    EXPORTAPI("writeItem", ItemStack*, bs->writeType(NetworkItemStackDescriptor(*value)));
    EXPORTAPI("writeString", std::string const&, bs->writeString(value));
    EXPORTAPI("writeCompoundTag", CompoundTag*, bs->writeCompoundTag(*value));
    EXPORTAPI2(writeBool);
    EXPORTAPI2(writeByte);
    EXPORTAPI2(writeDouble);
    EXPORTAPI2(writeFloat);
    EXPORTAPI2(writeSignedBigEndianInt);
    EXPORTAPI2(writeSignedInt);
    EXPORTAPI2(writeSignedInt64);
    EXPORTAPI2(writeSignedShort);
    EXPORTAPI2(writeUnsignedChar);
    EXPORTAPI2(writeUnsignedInt);
    EXPORTAPI2(writeUnsignedInt64);
    EXPORTAPI2(writeUnsignedShort);
    EXPORTAPI2(writeUnsignedVarInt);
    EXPORTAPI2(writeUnsignedVarInt64);
    EXPORTAPI2(writeVarInt);
    EXPORTAPI2(writeVarInt64);
}