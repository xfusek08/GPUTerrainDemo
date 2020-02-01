
#pragma once

namespace  gpd
{
    namespace interfaces
    {
        /**
         * Interface of the main loop used by Application
         * ! not used currently ... cannot avoid dependency on SDL_EVENT - custom event system is not implemented
         * ! GPD_EVENT doest not exists
         */
        class MainLoopInterface
        {
        public:
            virtual void init() = 0;
            virtual void run() = 0;
            virtual void addEventReceiver(std::shared_ptr<EventReceiverInterface>) = 0;
            virtual void setEventHandler(std::function<bool(GPD_EVENT const&)> const& handler) = 0;
            virtual void setDrawCallback(std::function<void()> const& callback) = 0;
        };
    }
}
