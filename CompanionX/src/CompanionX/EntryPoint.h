#pragma once

#ifdef CX_PLATFORM_WINDOWS

extern CompanionX::Application* CompanionX::CreateApplication();

int main(int argc, char** argv)
{
    CompanionX::Log::Init();
    CX_CORE_WARN("Initialized Log!");
    CX_INFO("Hello from Client!");


    auto app = CompanionX::CreateApplication();
    app->Run();
    delete app;
}

#endif // CX_PLATFORM_WINDOWS
