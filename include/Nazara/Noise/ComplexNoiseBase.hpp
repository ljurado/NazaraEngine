// Copyright (C) 2012 R�mi B�ges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef COMPLEXNOISEBASE_H
#define COMPLEXNOISEBASE_H

#include <Nazara/Prerequesites.hpp>
//#include <Nazara/Noise/NoiseBase.hpp>
#include "NoiseBase.hpp"

class NzComplexNoiseBase : public NzNoiseBase
{
    public:
        NzComplexNoiseBase();
        ~NzComplexNoiseBase();

        void SetLacunarity(float lacunarity);
        void SetHurstParameter(float h);
        void SetOctavesNumber(float octaves);
        void RecomputeExponentArray();

    protected:
        float m_lacunarity;
        float m_hurst;
        float m_octaves;
        float exponent_array[30];
        float m_sum;
    private:
        bool m_parametersModified;

};

#endif // COMPLEXNOISEBASE_H