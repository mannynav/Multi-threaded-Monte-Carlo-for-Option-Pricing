#pragma once

#ifndef Application_WrapperH
#define Application_WrapperH


class PseudoFactory;
class Output;
class Input;
class StopWatch;
class ApplicationBase;


class Application_Wrapper
{
public:
    Application_Wrapper();
    ~Application_Wrapper();

    void run();

private:
    PseudoFactory* fac_;
    Input* inp_;          // owns this pointer
    ApplicationBase* app_;
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif