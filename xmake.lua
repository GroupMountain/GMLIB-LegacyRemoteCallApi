add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")
add_repositories("miracleforest-repo https://github.com/MiracleForest/xmake-repo.git")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

add_requires("levilamina 26.10.10", {configs = {target_type = "server"}})
add_requires("legacyremotecall")
add_requires("levibuildscript 0.6.0")
add_requires("ilistenattentively 0.12.0")
add_requires("modapi 26.10.0",
            "zstr 1.0.8",
            "minizip-ng 4.0.9"
            )

rule("package_envs")
    before_link(function (target)

    end)
rule_end()

rule("linkrule")
    on_config(function(target)
        target:add("shflags", "/DELAYLOAD:bedrock_runtime.dll")
    end)

    before_link(function(target)

        print("Running prelink...")

        import("lib.detect.find_file")
        import("core.project.config")

        local plat = config.get("plat") or "windows"
        local arch = config.get("arch") or "x64"
        local target_type = config.get("target_type") or "server"

        local builddir = config.builddir()
        local outdir = path.join(builddir, ".prelink")
        local libdir = path.join(outdir, "lib")

        os.mkdir(libdir)

    local envs = os.joinenvs(target:pkgenvs(), os.getenvs())
    local searchpaths = path.splitenv(envs.PATH or envs.Path or envs.path or "")
    local data = assert(find_file("bedrock_runtime_data", searchpaths), "Cannot find bedrock_runtime_data ):")
    local link = assert(find_file("prelink.exe", searchpaths), "Cannot find prelink.exe ):")

        local inputs = table.copy(target:objectfiles())

        local gmlib_shared = assert(find_file("GMLIB.lib", {"sdk\\gmlib\\26.10.10\\shared\\lib"}), "Cannot find GMLIB.lib shared ):")
        local gmlib_static = assert(find_file("GMLIB.lib", {"sdk\\gmlib\\26.10.10\\static\\lib"}), "Cannot find GMLIB.lib static ):")
        table.insert(inputs, "legacy_stdio_definitions.lib")


        table.insert(inputs, gmlib_shared)
        table.insert(inputs, gmlib_static)
        for _, dep in ipairs(target:orderdeps()) do
            if dep:kind() == "static" then
                local libfile = dep:targetfile()
                if libfile and os.isfile(libfile) then
                    table.insert(inputs, libfile)
                end
            end
        end
        for _, pkg in ipairs(target:orderpkgs()) do
            for _, linkdir in ipairs(pkg:get("linkdirs")) do
                for _, link in pairs(pkg:get("links")) do
                    local libfile = path.join(linkdir, link .. ".lib")
                    if os.isfile(libfile) then
                        table.insert(inputs, libfile)
                        print(libfile)
                    end
                end
            end
        end


        os.execv(link, {
            string.format("%s-%s-%s", target_type, plat, arch),
            outdir,
            data,
            table.unpack(inputs)
        })

        target:add("linkdirs", libdir)
        target:add("links", "bedrock_runtime_api")
    end)

    after_link(function(target)
        os.rm("$(builddir)/.prelink/lib/*.lib")
    end)
rule_end()

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

        "modapi"
    )
        add_includedirs(
                    "sdk/gmlib/26.10.10/shared/include",
                    "sdk/gmlib/26.10.10/static/include",
            "src"


        )
    add_links(
        "sdk/gmlib/26.10.10/static/lib/GMLIB.lib",
        "sdk/gmlib/26.10.10/shared/lib/GMLIB.lib"
    )
    add_rules("package_envs")
    add_rules("linkrule")
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
