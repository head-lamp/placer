#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER
struct ComponentList {
    Physical phys_components[100];
    Renderable rend_components[100];
};

enum Components {
    PHYSICAL,
    RENDERABLE,
    COMPONENTS_TOTAL
};


Components get_comp_id(const char *name);
#endif
