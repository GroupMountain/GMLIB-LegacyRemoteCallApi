add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")
add_repositories("miracleforest-repo https://github.com/MiracleForest/xmake-repo.git")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

add_requires("levilamina 1.7.3", {configs = {target_type = "server"}})
add_requires("legacyremotecall")
add_requires("levibuildscript 0.5.2")
add_requires("ilistenattentively 0.10.0")
add_requires("gmlib 1.7.0")
add_requires("modapi 0.3.0")

target("GMLIB-LegacyRemoteCallApi")
    add_cxflags(
        "/EHa",
        "/utf-8",
        "/bigobj"
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
        "src"
    )
    add_packages(
        "levilamina",
        "legacyremotecall",
        "ilistenattentively",
        "gmlib",
        "modapi"
    )
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    set_exceptions("none")
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