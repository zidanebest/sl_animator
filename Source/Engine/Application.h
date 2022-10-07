#pragma once

namespace sl{
    class Application{
    private:
        Application(const Application&);
        Application& operator=(const Application&);
    public:
        inline         Application(){ }
        inline virtual ~Application(){ }

        inline virtual void Initialize(){ }
        inline virtual void Update(float delta_time){ }
        inline virtual void Render(float aspect_radio){ }
        inline virtual void Shutdown(){ }
    };
}
