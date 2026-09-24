#include "Global.h"

// BDS 26.51 no longer exports these symbols from the server binary; the headers still declare them
// (26.51 declares ItemInstance's default constructor for the client only), so the definitions live
// here instead of coming out of the archives. ItemInstance and RecipeIngredient add no members of
// their own, which makes the constructors below complete.

ItemInstance::ItemInstance() : ItemStackBase() {}

ItemDescriptor::ItemDescriptor(ItemDescriptor const& rhs) { *this = rhs; }

ItemDescriptorCount::ItemDescriptorCount() : mStackSize(0) {}

namespace Bedrock {
StaticOptimizedString::StaticOptimizedString() : mData{} {}
} // namespace Bedrock
