#pragma once

#include <memory>
#include <map>

#include <GeoPlanetDemo/vt/VisualizationTechnique.h>

#define REGISTER_VT_TYPE(vt_class)\
namespace gpd {\
    namespace vt {\
        namespace types {\
            const VTType vt_class = #vt_class;\
        }\
        class vt_class##Factory : public VTFactorySpecific\
        {\
        public:\
            vt_class##Factory()\
            {\
                VTFactory::registerType(types::vt_class, this);\
            }\
            virtual std::shared_ptr<VisualizationTechnique> create(const VTType& type, std::shared_ptr<ge::gl::Context> gl) override\
            {\
                return std::make_shared<vt_class>(type, gl);\
            }\
        };\
        static vt_class##Factory global_##vt_class##Factory;\
    }\
}

namespace ge
{
    namespace gl
    {
        class Context;
    }
}

namespace gpd
{
    namespace vt
    {
        class VTFactorySpecific
        {
        public:
            virtual std::shared_ptr<VisualizationTechnique> create(const VTType& type, std::shared_ptr<ge::gl::Context> gl) = 0;
        };

        class VTFactory
        {
        public:
            // static methods
            static std::shared_ptr<VisualizationTechnique> create(const VTType& type, std::shared_ptr<ge::gl::Context> gl)
            {
                if (getMap().find(type) == getMap().end()) {
                    return nullptr;
                }

                return getMap()[type]->create(type, gl);
            }

            static std::map<VTType, VTFactorySpecific*>& getMap()
            {
                static std::map<VTType, VTFactorySpecific*> map;
                return map;
            }

            static void registerType(const VTType& type, VTFactorySpecific* factory)
            {
                getMap()[type] = factory;
            }

            static std::vector<VTType> list()
            {
                std::vector<VTType> result;
                result.reserve(getMap().size());
                for(auto item : getMap()) {
                    result.push_back(item.first);
                }
                return result;
            }
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(VisualizationTechnique)
