#pragma once

#ifdef CX_PLATFORM_WINDOWS

extern CompanionX::Application* CompanionX::CreateApplication();

int main(int argc, char** argv)
{
    printf("Hello, World!\n");
    auto app = CompanionX::CreateApplication();
    app->Run();
    delete app;
}

#endif // CX_PLATFORM_WINDOWS
