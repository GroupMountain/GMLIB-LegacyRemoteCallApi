add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")
add_repositories("miracleforest-repo https://github.com/MiracleForest/xmake-repo.git")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end
set_toolchains("clang-cl")
add_requires("levilamina 26.20.0", {configs = {target_type = "server"}})
add_requires("legacyremotecall")
add_requires("levibuildscript 0.6.0")
add_requires("ilistenattentively 0.13.0")
add_requires("gmlib 26.20.0", "modapi 26.20.0")
add_requires("zstr 1.0.8", "minizip-ng 4.0.9")

target("GMLIB-LegacyRemoteCallApi")
    add_cxflags(
        "/utf-8",
        "/bigobj"
    )
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_HAS_CXX23=1"
    )
    add_defines("LL_PLAT_S")  --TODO: check client compatibility
    add_files(
        "src/**.cpp"
    )
    add_packages(
        "levilamina",
        "legacyremotecall",
        "levibuildscript",
        "ilistenattentively",
        "zstr",
        "minizip-ng",
        "modapi",
        "gmlib"
    )
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    set_exceptions("cxx")
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    after_build(function (target)
        local target_path = path.join("bin", target:name(), "lib")
        if os.exists(target_path) then 
            os.rm(target_path)
        end
        os.cp("lib", target_path)
    end)
