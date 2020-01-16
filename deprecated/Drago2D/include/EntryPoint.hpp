

extern d2d::Application * d2d::CreateApplication();

int main()
{
    d2d::Log::Init();
    D2D_LOG_CORE_INFO("Started Log!");

    D2D_LOG_CORE_INFO("Creating application backend!");
    d2d::Application * app = d2d::CreateApplication();
    D2D_LOG_CORE_INFO("Created Application!");
    D2D_LOG_CORE_INFO("Starting app!");
    app->Run();
    D2D_LOG_CORE_INFO("Done!\nDeleting app!");
    delete app;
}
