//=====================================
//
//MophingMeshContainer.h
//�@�\:���[�t�B���O���b�V���R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOPHINGMESHCONTAINER_H_
#define _MOPHINGMESHCONTAINER_H_

#include "../../main.h"
#include "MeshContainer.h"

#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MophingMeshContainer : public MeshContainer
{
public:
	MophingMeshContainer();
	virtual ~MophingMeshContainer();

	void RegisterVertex(unsigned index);

private:
	std::vector<LPDIRECT3DVERTEXBUFFER9> vtxContainer;
};
#endif