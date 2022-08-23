#include "Terrain.h"

Terrain::Terrain()
{
}

void Terrain::draw(RenderTarget* renderTarget, RenderState state)
{
    state.modelMatrix = modelMatrix * state.modelMatrix;

}
