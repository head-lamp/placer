struct ComponentList {
    Physical phys_components[100];
    Renderable rend_components[100];
};

enum Components {
    PHYSICAL,
    RENDERABLE,
    COMPONENTS_TOTAL
};

const char *COMPONENTS_NAMES[] = {
    "physical",
    "renderable",
};

Components get_comp_id(const char *name);
