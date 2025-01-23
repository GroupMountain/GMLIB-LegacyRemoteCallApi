add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

add_requires("levilamina 1.0.0-rc.3", {configs = {target_type = "server"}})
add_requires("legacyremotecall 0.9.0-rc.1")
add_requires("gmlib 0.13.10")
add_requires("levibuildscript 0.3.0")

target("GMLIB-LegacyRemoteCallApi")
    add_cxflags(
        "/EHa",
        "/utf-8"
    )
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_HAS_CXX17",
        "_HAS_CXX20",
        "_HAS_CXX23"
    )
    add_files(
        "src/**.cpp"
    )
    add_includedirs(
        "src"
    )
    add_packages(
        "levilamina",
        "legacyremotecall",
        "gmlib"
    )
    add_rules("@levibuildscript/linkrule")
    set_exceptions("none")
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")

    after_build(function (target)
        local plugin_packer = import("scripts.after_build")

        local plugin_define = {
            pluginName = target:name(),
            pluginFile = path.filename(target:targetfile()),
        }
        
        plugin_packer.pack_plugin(target,plugin_define)
    end)
