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

#define EXPORTAPI(funcName, type, fuc)                                                                                 \
    RemoteCall::exportAs("GMLIB_BinaryStream_API", funcName, [](uint64 BinaryStreamId, type value) -> void {           \
        auto binaryStream = LegacyScriptBinaryStreamManager::getInstance().getBinaryStream(BinaryStreamId);            \
        if (binaryStream != nullptr) fuc;                                                                              \
    })

template <typename T>
struct Info;
template <typename T, typename R, typename A, typename... AS>
struct Info<R (T::*)(A, AS...)> {
    using ArgT = A;
};
#define EXPORTAPI2(T) EXPORTAPI(#T, Info<decltype(&GMLIB_BinaryStream::T)>::ArgT, binaryStream->T(value))

void Export_BinaryStream_API() {
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "create", []() -> uint64 {
        auto id = LegacyScriptBinaryStreamManager::getInstance().getNextId();
        LegacyScriptBinaryStreamManager::getInstance().cretateBinaryStream(id);
        return id;
    });
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "reset", [](uint64 BinaryStreamId) -> void {
        if (LegacyScriptBinaryStreamManager::getInstance().getBinaryStream(BinaryStreamId) == nullptr)
            LegacyScriptBinaryStreamManager::getInstance().cretateBinaryStream(BinaryStreamId);
        LegacyScriptBinaryStreamManager::getInstance().getBinaryStream(BinaryStreamId)->reset();
    });
    RemoteCall::exportAs(
        "GMLIB_BinaryStream_API",
        "sendTo",
        [](uint64 BinaryStreamId, Player* player) -> void {
            auto binaryStream = LegacyScriptBinaryStreamManager::getInstance().getBinaryStream(BinaryStreamId);
            if (binaryStream != nullptr) binaryStream->sendTo(*player);
        }
    );
    RemoteCall::exportAs("GMLIB_BinaryStream_API", "destroy", [](uint64 BinaryStreamId) -> void {
        LegacyScriptBinaryStreamManager::getInstance().removeBinaryStream(BinaryStreamId);
    });
    EXPORTAPI("writePacketHeader", int, binaryStream->writePacketHeader((MinecraftPacketIds)value));
    EXPORTAPI("writeUuid", std::string const&, binaryStream->writeUuid(mce::UUID::fromString(value)));
    EXPORTAPI("writeItem", ItemStack*, NetworkItemStackDescriptor(*value).write(*binaryStream));
    EXPORTAPI("writeString", std::string const&, binaryStream->writeString(value));
    EXPORTAPI("writeCompoundTag", CompoundTag*, binaryStream->writeCompoundTag(*value));
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