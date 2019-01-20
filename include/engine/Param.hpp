#pragma once
#include "common.hpp"
#include <jansson.h>


namespace rack {


struct ParamQuantity;


struct ParamQuantityFactory {
	virtual ~ParamQuantityFactory() {}
	virtual ParamQuantity *create() = 0;
};


struct Param {
	float value = 0.f;

	float minValue = 0.f;
	float maxValue = 1.f;
	float defaultValue = 0.f;

	/** The name of the parameter in sentence capitalization
	e.g. "Frequency", "Pulse width", "Alternative mode"
	*/
	std::string label;
	/** The numerical unit of measurement
	Use a space before non-abbreviations to separate the numerical value.
	e.g. " semitones", "Hz", "%", "V"
	*/
	std::string unit;
	/** Set to 0 for linear, nonzero for exponential */
	float displayBase = 0.f;
	float displayMultiplier = 1.f;
	/** An optional one-sentence description of the parameter */
	std::string description;
	ParamQuantityFactory *paramQuantityFactory = NULL;

	~Param() {
		if (paramQuantityFactory)
			delete paramQuantityFactory;
	}

	template<class TParamQuantity = ParamQuantity>
	void config(float minValue, float maxValue, float defaultValue, std::string label = "", std::string unit = "", float displayBase = 0.f, float displayMultiplier = 1.f) {
		this->value = defaultValue;
		this->minValue = minValue;
		this->maxValue = maxValue;
		this->defaultValue = defaultValue;
		if (!label.empty())
			this->label = label;
		this->unit = unit;
		this->displayBase = displayBase;
		this->displayMultiplier = displayMultiplier;

		struct TParamQuantityFactory : ParamQuantityFactory {
			ParamQuantity *create() override {return new TParamQuantity;}
		};
		if (paramQuantityFactory)
			delete paramQuantityFactory;
		paramQuantityFactory = new TParamQuantityFactory;
	}

	float getValue() {
		return value;
	}

	void setValue(float value) {
		this->value = value;
	}

	bool isBounded();
	json_t *toJson();
	void fromJson(json_t *rootJ);
	void reset();
	void randomize();
};


} // namespace rack
