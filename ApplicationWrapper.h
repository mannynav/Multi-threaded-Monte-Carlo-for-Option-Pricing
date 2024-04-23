#pragma once

#ifndef Application_WrapperH
#define Application_WrapperH


class PseudoFactory;
class ApplicationBase;
class Input;


class Application_Wrapper
{
public:
    Application_Wrapper();
    ~Application_Wrapper();
    void run() const;

private:
    std::unique_ptr<PseudoFactory> fac_;
    std::unique_ptr<ApplicationBase> app_;
    Input* inp_;
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif