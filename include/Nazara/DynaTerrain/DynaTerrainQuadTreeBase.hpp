// Copyright (C) 2012 R�mi B�ges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNATERRAINQUADTREEBASE_HPP
#define NAZARA_DYNATERRAINQUADTREEBASE_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/DynaTerrain/TerrainNode.hpp>
#include <Nazara/DynaTerrain/Dispatcher.hpp>
#include <Nazara/DynaTerrain/ObjectPool.hpp>
#include <Nazara/DynaTerrain/TerrainNodeID.hpp>
#include <Nazara/DynaTerrain/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/PlanetConfiguration.hpp>
#include <Nazara/DynaTerrain/HeightSource2D.hpp>
#include <Nazara/DynaTerrain/HeightSource3D.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <Nazara/Core/Clock.hpp>

class NAZARA_API NzDynaTerrainQuadTreeBase
{
    public:
        friend class NzTerrainNode;

        NzDynaTerrainQuadTreeBase(const NzTerrainConfiguration& configuration, NzHeightSource2D* heightSource);
        NzDynaTerrainQuadTreeBase(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource, const NzEulerAnglesf& quadtreeOrientation = NzEulerAnglesf(0.f,0.f,0.f));
        ~NzDynaTerrainQuadTreeBase();

        void ConnectNeighbor(NzDynaTerrainQuadTreeBase* neighbour, nzDirection direction);

        void DisconnectNeighbor(NzDynaTerrainQuadTreeBase* neighbour, nzDirection direction);

        NzDynaTerrainQuadTreeBase* GetContainingQuadTree(const NzTerrainNodeID& nodeID);
        unsigned int GetLeafNodesAmount() const;
        float GetMaximumHeight() const;
        NzTerrainNode* GetNode(const NzTerrainNodeID& nodeID);
        NzTerrainNode* GetRootNode();
        unsigned int GetSubdivisionsAmount();
        virtual NzVector3f GetVertexPosition(const NzTerrainNodeID& nodeID, int x, int y);

        void Initialize();

        void Render();

        void Update(const NzVector3f& cameraPosition);

    protected:
        nzQuadTreeType m_type;
        NzTerrainNode* GetNodeFromPool();
        void ReturnNodeToPool(NzTerrainNode* node);
        NzPatch* GetPatchFromPool();
        void ReturnPatchToPool(NzPatch* patch);
        //Vu que quadtree ne sera pas en charge de l'affichage, elles sont peut �tre inutiles, y compris maintenir � jour m_leaves
        void RegisterLeaf(NzTerrainNode* node);
        bool UnRegisterLeaf(NzTerrainNode* node);//Les feuilles enlev�es ici doivent aussi l'�tre de la camera list
        bool UnRegisterNode(NzTerrainNode* node);

        void AddLeaveToSubdivisionQueue(NzTerrainNode* node);
        void AddNodeToRefinementQueue(NzTerrainNode* node);
        void TryRemoveNodeFromRefinementQueue(NzTerrainNode* node);

        //Returns -1 if the distance to the camera is too big
        //or the radius index otherwise
        virtual int TransformDistanceToCameraInRadiusIndex(float distance);

        NzDispatcher m_dispatcher;

        NzTerrainConfiguration m_terrainConfiguration;
        NzPlanetConfiguration m_planetConfiguration;
        NzDynaTerrainConfigurationBase m_commonConfiguration;
        //-------
        NzHeightSource2D* m_heightSource2D;
        NzHeightSource3D* m_heightSource3D;

        NzTerrainNode* m_root;
        TerrainNodeData m_data;

        NzMatrix4f m_rotationMatrix;
        //-------

        NzDynaTerrainQuadTreeBase* m_neighbours[4];

        std::map<float,unsigned int> m_cameraRadiuses;
        std::map<float,unsigned int>::iterator it;

        std::map<NzTerrainNodeID,NzTerrainNode*> m_nodesMap;
        std::list<NzTerrainNode*> m_leaves;

        NzObjectPool<NzTerrainNode> m_nodesPool;
        NzObjectPool<NzPatch> m_patchesPool;

        std::map<NzTerrainNodeID,NzTerrainNode*> m_subdivisionQueue;
        std::map<NzTerrainNodeID,NzTerrainNode*> m_refinementQueue;

        unsigned int m_subdivisionsAmount;
        unsigned int m_poolReallocationSize;
        unsigned int m_poolAllocatedSpace;

        unsigned int m_maxOperationsPerFrame;

        NzClock updateClock;

        bool m_isInitialized;

    private:
        void Construct();

};

#endif // NAZARA_DYNATERRAINQUADTREEBASE_HPP