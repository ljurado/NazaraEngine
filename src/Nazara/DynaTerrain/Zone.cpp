// Copyright (C) 2012 R�mi B�ges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include "Zone.hpp"
#include <iostream>
#include "Dispatcher.hpp"

NzZone::NzZone(NzDispatcher* dispatcher)
{
    m_dispatcher = dispatcher;
}

NzZone::~NzZone()
{
    //dtor
}

void NzZone::AddBuffer(NzVertexBuffer* buffer)
{
    m_buffers.push_back(buffer);
    m_buffersMap.AddEmptyBuffer();

    //Un buffer contient 1750 emplacements

    /*
    for(int i(0) ; i < 1750 ; ++i)
    {
        nzBufferLocation temp;
        temp.buffer = m_buffers.size() - 1;
        temp.index = i*25;
        //On rajoute l'index de l'emplacement � la file des index libres
        m_freeSpotsIndex.push_back(temp);
    }

    xid ID;
    ID.dummy = true;
    ID.freeAdjacentConsecutiveSlots = 1750;
    std::list<xid> temp;
    temp.push_back(ID);
    m_sparseBuffers.push_back(temp);*/

    std::cout<<"Added Buffer"<<std::endl;
}

void NzZone::AddPatch(const std::array<float,150>& vertices, const id& ID)
{
    //std::cout<<"Adding patch "<<ID.lvl<<"|"<<ID.sx<<"|"<<ID.sy<<std::endl;

    //Si la zone n'a pas de slots de libre, elle demande un buffer suppl�mentaire au dispatcher
    if(m_buffersMap.GetTotalFreeSlotsAmount() == 0)
    {
        NzVertexBuffer* temp = m_dispatcher->QueryFreeBuffer();
        if(temp != nullptr)
        {
            //On a bien re�u un buffer, on peut poursuivre
            this->AddBuffer(temp);
        }
        else //Si le dispatcher ne peut en fournir aucun, l'op�ration est temporairement abandonn�e et le patch est sauvegard� dans une file
        {
            for(int i(0) ; i < 150 ; ++i)
            {
                m_unbufferedPatches.push(vertices.at(i));
                m_unbufferedPatchesIndex.push(ID);
            }
            return;
        }
    }

    nzBufferLocation location = m_buffersMap.InsertValue(ID);

    if(location.buffer < 0)
        return;

    //La zone a des slots de libres, on remplit le buffer avec les vertices
    if(!m_buffers.at(location.buffer)->Fill(vertices.data(),location.index,25))
    {
        std::cout<<"Cannot fill buffer"<<std::endl;
        return;
    }
}

void NzZone::DrawBuffers() const
{


    //For each buffer
    for(unsigned int i(0) ; i < m_buffers.size() ; ++i)
    {

        //we recover consecutive vertices block amount
        /*for(std::list<NzVector2ui>::iterator it = m_buffersMap.at(i).GetVerticeIndexBatches().begin();
                                             it != m_buffersMap.at(i).GetVerticeIndexBatches().end() ;
                                             it++)
        {
            //We render each vertice batch in a single call to reduce draw calls
            NzRenderer::SetVertexBuffer(m_buffers.at(i));

            // On fait le rendu
                //(*it).x -> firstIndex;
                //(*it).y -> vertexCount;
            NzRenderer::DrawIndexedPrimitives(nzPrimitiveType_TriangleFan, (*it).x, (*it).y);
        }*/
    }
}

unsigned int NzZone::GetFreeBuffersAmount()
{
    return m_buffersMap.GetFreeBuffersAmount();
}

unsigned int NzZone::GetFreeSlotsAmount()
{
    return m_buffersMap.GetTotalFreeSlotsAmount();
}

void NzZone::Optimize(int amount)
{
    //Here we try to reduce fragmentation in the vertex buffers
        //the image buffer indicates us where to move the raw data

    for(int i(0) ; i < amount ; ++i)
    {
        //We recover the initial and final position
        NzVector2<nzBufferLocation> move_data = m_buffersMap.ReduceFragmentation();

        //If there is no fragmentation
        if(move_data.x.index < 0)
            return;

        //We reduce fragmentation by moving 1 patch from one position to an other
            //We copy the original data
        //m_buffers.
            //To the new location
        //m_buffers.
    }
}

bool NzZone::RemoveFreeBuffer(NzVertexBuffer* buffer)
{
    return false;
}

bool NzZone::RemovePatch(const id& ID)
{
    return m_buffersMap.RemoveValue(ID);
}

bool NzZone::UpdatePatch(const std::array<float,150>& vertices, const id& ID)
{
    nzBufferLocation location = m_buffersMap.UpdateValue(ID);

    //Si l'emplacement n'a pas �t� retrouv�, on abandonne
    if(location.buffer < 0)
        return false;

    if(!m_buffers.at(location.buffer)->Fill(vertices.data(),location.index,25))
    {
        std::cout<<"Cannot fill buffer"<<std::endl;
        return false;
    }

    return true;
}