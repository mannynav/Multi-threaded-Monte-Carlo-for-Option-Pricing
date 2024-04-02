#pragma once

#ifndef ApplicationBaseH
#define ApplicationBaseH


class Output;


class ApplicationBase
{
public:
    virtual ~ApplicationBase() {}

    virtual void run() = 0;
};

#endif