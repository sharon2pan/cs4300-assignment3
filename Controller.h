#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "View.h"
#include "Model.h"

class Controller
{
public:
    Controller(Model& m,View& v);
    ~Controller();
    void run();
private:
    void createModels();
    View view;
    Model model;
    float time;
};

#endif