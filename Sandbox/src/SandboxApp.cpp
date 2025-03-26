#include <CompanionX.h>

class Sandbox : public CompanionX::Application
{
  public:
    Sandbox()
    {
      
    }

    ~Sandbox()
    {

    }
};

CompanionX::Application* CompanionX::CreateApplication()
{
  return new Sandbox();
}
