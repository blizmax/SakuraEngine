includes("EngineUtils")

static_module("Core", EngineVersion, "Core.cpp")
    add_deps("EngineUtils")

shared_module("CoreModule", EngineVersion, "CoreModule.cpp")
    add_deps("Core", "SPA")