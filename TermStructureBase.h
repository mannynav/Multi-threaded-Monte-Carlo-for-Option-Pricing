#pragma once


class ModelBase;

class TermStructureBase
{

public:

	virtual ~TermStructureBase() = default;
	virtual double Get_MT(const ModelBase& model) const = 0;

private:
	
};

