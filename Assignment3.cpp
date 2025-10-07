//! [code]

#include "Model.h"
#include "View.h"
#include "Controller.h"


int main(void)
{
    Model model;
    View view;
    Controller controller(model,view);
    controller.run();
}

//! [code]
