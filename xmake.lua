add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")
add_repositories("miracleforest-repo https://github.com/MiracleForest/xmake-repo.git")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

add_requires("levilamina", {configs = {target_type = "server"}})
add_requires("legacyremotecall")
add_requires("levibuildscript")
add_requires("ilistenattentively")
 
target("GMLIB-LegacyRemoteCallApi")
    add_cxflags(
        "/EHa",
        "/utf-8"
    )
    add_defines(
        "NOMINMAX",
        "UNICODE", 
        "_HAS_CXX23=1"
    )
    add_files(
        "src/**.cpp"
    )
    add_includedirs(
        "src",
        "../GMLIB/bin/SDK/include"
    )
    add_links("../GMLIB/bin/SDK/lib/GMLIB.lib")
    add_packages(
        "levilamina",
        "legacyremotecall",
        "ilistenattentively"
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
