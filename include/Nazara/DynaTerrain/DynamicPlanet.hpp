// Copyright (C) 2012 R�mi B�ges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNAMICPLANET_HPP
#define NAZARA_DYNAMICPLANET_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource3D.hpp>
#include <Nazara/Renderer/Shader.hpp>
#include <Nazara/DynaTerrain/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/DynaTerrainQuadTreeBase.hpp>
#include <Nazara/DynaTerrain/Dispatcher.hpp>
#include <Nazara/DynaTerrain/ObjectPool.hpp>
#include <Nazara/Renderer/Texture.hpp>

//TODO : modifier shader du terrain pour qu'il fonctionne avec n'importe quelle direction (slope, altitude)

class NAZARA_API NzDynamicPlanet
{
    public:

        NzDynamicPlanet(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource);
        ~NzDynamicPlanet();

        void Initialize();

        void Render();

        bool SetShaders(const NzString& vertexShader, const NzString& fragmentShader);

        void Update(const NzVector3f& cameraPosition);

    private:

        NzPlanetConfiguration m_configuration;
        NzHeightSource3D* m_heightSource;
        NzTexture m_terrainTexture;

        NzShader m_shader;
        NzDynaTerrainQuadTreeBase* quadtree;
        NzDynaTerrainQuadTreeBase* quadtree2;
};

#endif // NAZARA_DYNAMICPLANET_HPP