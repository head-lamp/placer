#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

#define INITIAL_COMPONENT_SIZE 100
struct ComponentList {
    Physical phys_components[INITIAL_COMPONENT_SIZE];
    Renderable rend_components[INITIAL_COMPONENT_SIZE];
};

enum Components {
    PHYSICAL,
    RENDERABLE,
    COMPONENTS_TOTAL
};


Components get_comp_id(const char *name);
#endif
