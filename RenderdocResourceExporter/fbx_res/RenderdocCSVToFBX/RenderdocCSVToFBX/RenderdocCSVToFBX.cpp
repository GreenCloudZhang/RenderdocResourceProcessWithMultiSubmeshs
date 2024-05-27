// RenderdocCSVToFBX.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <cstdlib>
#include <iostream>
#include <set>

#include <fbxsdk.h>

#include "CSVFile.h"
#include "CommonMath.h"

using namespace std;

struct MeshVertex
{
	float x = 0.f, y = 0.f, z = 0.f;

	float nx = 0.f, ny = 0.f, nz = 0.f;
	float tx = 0.f, ty = 0.f, tz = 0.f, tw = 0.f;

	float cr = 0.f, cg = 0.f, cb = 0.f, ca = 0.f;

	float u = 0.f, v = 0.f;
	float u2 = 0.f, v2 = 0.f;
	float u3 = 0.f, v3 = 0.f;
};

void ConvertCSV2FBX(const char* sourceCSVFile, 
	bool export_normal, bool export_tangent, bool export_color,
	bool export_uv, bool export_uv2, bool export_uv3)
{
	FbxManager* sdkManager;
	FbxIOSettings* ioSettings;
	FbxScene* scene;

	sdkManager = FbxManager::Create();

	ioSettings = FbxIOSettings::Create(sdkManager, IOSROOT);
	ioSettings->SetBoolProp(EXP_FBX_MATERIAL, true);
	ioSettings->SetBoolProp(EXP_FBX_TEXTURE, true);
	ioSettings->SetBoolProp(EXP_FBX_EMBEDDED, true);
	ioSettings->SetBoolProp(EXP_FBX_ANIMATION, true);
	ioSettings->SetBoolProp(EXP_FBX_SHAPE, true);
	ioSettings->SetIntProp(
		EXP_FBX_EXPORT_FILE_VERSION, FBX_FILE_VERSION_7400);

	sdkManager->SetIOSettings(ioSettings);
	scene = FbxScene::Create(sdkManager, "");

	CCSVFile* pSrcFile = new CCSVFile(sourceCSVFile);

	std::map<int, MeshVertex> verticsMap;//CSV VertexID
	int iVertexID = 0;
	std::map<int, int> remapVertexIDNew2Old;
	std::map<int, int> remapVertexIDOld2New;
	for (int iRow = 0; iRow < pSrcFile->GetRowNum(); iRow++)
	{
		pSrcFile->GetCellValue("IDX", iRow, iVertexID);

		if (verticsMap.find(iVertexID) == verticsMap.end())
		{
			int newVertexID = verticsMap.size();
			remapVertexIDNew2Old[newVertexID] = iVertexID;
			remapVertexIDOld2New[iVertexID] = newVertexID;
			pSrcFile->GetCellValue("POSITION.x", iRow, verticsMap[iVertexID].x);
			pSrcFile->GetCellValue("POSITION.y", iRow, verticsMap[iVertexID].y);
			pSrcFile->GetCellValue("POSITION.z", iRow, verticsMap[iVertexID].z);

			if(export_normal)
			{
				pSrcFile->GetCellValue("NORMAL.x", iRow, verticsMap[iVertexID].nx);
				pSrcFile->GetCellValue("NORMAL.y", iRow, verticsMap[iVertexID].ny);
				pSrcFile->GetCellValue("NORMAL.z", iRow, verticsMap[iVertexID].nz);
			}
			if(export_tangent)
			{
				pSrcFile->GetCellValue("TANGENT.x", iRow, verticsMap[iVertexID].tx);
				pSrcFile->GetCellValue("TANGENT.y", iRow, verticsMap[iVertexID].ty);
				pSrcFile->GetCellValue("TANGENT.z", iRow, verticsMap[iVertexID].tz);
				pSrcFile->GetCellValue("TANGENT.w", iRow, verticsMap[iVertexID].tw);
			}
			if (export_color)
			{
				pSrcFile->GetCellValue("COLOR.x", iRow, verticsMap[iVertexID].cr);
				pSrcFile->GetCellValue("COLOR.y", iRow, verticsMap[iVertexID].cg);
				pSrcFile->GetCellValue("COLOR.z", iRow, verticsMap[iVertexID].cb);
				pSrcFile->GetCellValue("COLOR.w", iRow, verticsMap[iVertexID].ca);
			}

			if(export_uv)
			{
				pSrcFile->GetCellValue("TEXCOORD0.x", iRow, verticsMap[iVertexID].u);
				pSrcFile->GetCellValue("TEXCOORD0.y", iRow, verticsMap[iVertexID].v);
			}
			if(export_uv2)
			{
				pSrcFile->GetCellValue("TEXCOORD1.x", iRow, verticsMap[iVertexID].u2);
				pSrcFile->GetCellValue("TEXCOORD1.y", iRow, verticsMap[iVertexID].v2);
			}
			if(export_uv3)
			{
				pSrcFile->GetCellValue("TEXCOORD2.x", iRow, verticsMap[iVertexID].u3);
				pSrcFile->GetCellValue("TEXCOORD2.y", iRow, verticsMap[iVertexID].v3);
			}
		}
	}

	int iTotalVerticsCount = verticsMap.size();

	// 用csv的文件名作为mesh的名字
	std::string meshName = sourceCSVFile;
	replace(meshName.begin(), meshName.end(), '/', '\\');
	meshName = meshName.substr(0, meshName.size() - 4);
	int pos = meshName.find_last_of('\\');
	if (pos != std::string::npos)
	{
		meshName = meshName.substr(pos + 1, meshName.size() - pos - 1);
	}

	FbxNode* rootNode = scene->GetRootNode();
	FbxNode* subshapeNode = FbxNode::Create(rootNode, meshName.c_str());

	// convert fbx mesh file
	FbxMesh* meshFbx = FbxMesh::Create(subshapeNode, subshapeNode->GetName());

	FbxGeometryElementNormal* meshNormal = NULL;
	FbxGeometryElementTangent* meshTangent = NULL;
	FbxLayerElementVertexColor* meshColor = NULL;
	FbxGeometryElementUV* meshUV = NULL;
	FbxGeometryElementUV* meshUV2 = NULL;
	FbxGeometryElementUV* meshUV3 = NULL;

	if(export_normal)
	{
		meshNormal = meshFbx->CreateElementNormal();
	}
	if(export_tangent)
	{
		meshTangent = meshFbx->CreateElementTangent();
	}
	if (export_color)
	{
		meshColor = meshFbx->CreateElementVertexColor();
	}

	if(export_uv)
	{
		meshUV = meshFbx->CreateElementUV("UV");
	}
	if(export_uv2)
	{
		meshUV2 = meshFbx->CreateElementUV("UV1");
	}
	if(export_uv3)
	{
		meshUV3 = meshFbx->CreateElementUV("UV2");
	}

	meshFbx->InitControlPoints(iTotalVerticsCount);

	if(export_normal)
	{
		meshNormal->SetMappingMode(FbxGeometryElementNormal::eByControlPoint);
		meshNormal->SetReferenceMode(FbxGeometryElementNormal::eDirect);
	}
	if(export_tangent)
	{
		meshTangent->SetMappingMode(FbxGeometryElementTangent::eByControlPoint);
		meshTangent->SetReferenceMode(FbxGeometryElementTangent::eDirect);
	}
	if (export_color)
	{
		meshColor->SetMappingMode(FbxGeometryElementTangent::eByControlPoint);
		meshColor->SetReferenceMode(FbxGeometryElementTangent::eDirect);
	}

	if(export_uv)
	{
		meshUV->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}
	if(export_uv2)
	{
		meshUV2->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV2->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}
	if(export_uv3)
	{
		meshUV3->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV3->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}

	FbxVector4* meshVectors = meshFbx->GetControlPoints();
	Matrix44 matRot;
	MatrixRotationZ(&matRot, -FLT_DTOR(0));

	for (int id = 0; id < verticsMap.size(); id++)
	{
		int index = remapVertexIDNew2Old[id];
		Vector3 Vertex(
			verticsMap[index].x * 100, verticsMap[index].y * 100, verticsMap[index].z * 100);
		Vec3TransformCoord(&Vertex, &Vertex, &matRot);
		meshVectors[id].Set(Vertex.x, Vertex.y, Vertex.z);

		if(export_normal)
		{
			Vector3 VertexNormal(
				verticsMap[index].nx, verticsMap[index].ny, verticsMap[index].nz);
			Vec3TransformNormal(&VertexNormal, &VertexNormal, &matRot);

			meshNormal->GetDirectArray().Add(
				FbxVector4(VertexNormal.x, VertexNormal.y, VertexNormal.z, 0));
		}
		if(export_tangent)
		{
			Vector4 VertexTangent(
				verticsMap[index].tx, verticsMap[index].ty, verticsMap[index].tz, verticsMap[index].tw);
			VertexTangent = VertexTangent * matRot;

			meshTangent->GetDirectArray().Add(
				FbxVector4(VertexTangent.x, VertexTangent.y, VertexTangent.z, VertexTangent.w));
		}
		if (export_color)
		{
			meshColor->GetDirectArray().Add(FbxVector4(verticsMap[index].cr, verticsMap[index].cg, verticsMap[index].cb, verticsMap[index].ca));
		}		
		if(export_uv)
		{
			meshUV->GetDirectArray().Add(
				FbxVector2(verticsMap[index].u, verticsMap[index].v));
		}
		if(export_uv2)
		{
			meshUV2->GetDirectArray().Add(
				FbxVector2(verticsMap[index].u2, verticsMap[index].v2));
		}
		if(export_uv3)
		{
			meshUV3->GetDirectArray().Add(
				FbxVector2(verticsMap[index].u3, verticsMap[index].v3));
		}
	}

	int iFaceID = 0;
	for (int iRow = 0; iRow < pSrcFile->GetRowNum(); iRow += 3)
	{
		meshFbx->BeginPolygon(0);

		pSrcFile->GetCellValue("IDX", iRow, iFaceID);
		meshFbx->AddPolygon(remapVertexIDOld2New[iFaceID]);
		pSrcFile->GetCellValue("IDX", iRow + 1, iFaceID);
		meshFbx->AddPolygon(remapVertexIDOld2New[iFaceID]);
		pSrcFile->GetCellValue("IDX", iRow + 2, iFaceID);
		meshFbx->AddPolygon(remapVertexIDOld2New[iFaceID]);

		meshFbx->EndPolygon();
	}

	subshapeNode->SetNodeAttribute(meshFbx);
	subshapeNode->SetShadingMode(FbxNode::eTextureShading);

	// save fbx
	std::string fbxFilePath = sourceCSVFile;
	fbxFilePath = fbxFilePath.substr(0, fbxFilePath.size() - 3);
	fbxFilePath += "fbx";

	int startIndex = fbxFilePath.find_last_of('\\');
	std::string fileName = fbxFilePath.substr(startIndex + 1);

	FbxExporter* exporter = FbxExporter::Create(sdkManager, fileName.c_str());
	if (!exporter->Initialize(fbxFilePath.c_str(), -1, ioSettings))
	{
		fprintf(stderr, "Failed to initialize FBX exporter\n");
		exporter->Destroy();
		return;
	}
	exporter->SetFileExportVersion(FBX_2014_00_COMPATIBLE);

	if (!exporter->Export(scene))
	{
		fprintf(stderr, "Failed to produce FBX file\n");
		exporter->Destroy();
		return;
	}

	exporter->Destroy();
}

void MergeCSVsToFBX(std::vector<std::string>& csvFiles, bool export_normal, bool export_tangent, bool export_color,
	bool export_uv, bool export_uv2, bool export_uv3)
{
	//support the same buffer and not, id attention ,pos/uv/ equal to judge
	FbxManager* sdkManager;
	FbxIOSettings* ioSettings;
	FbxScene* scene;

	sdkManager = FbxManager::Create();

	ioSettings = FbxIOSettings::Create(sdkManager, IOSROOT);
	ioSettings->SetBoolProp(EXP_FBX_MATERIAL, true);
	ioSettings->SetBoolProp(EXP_FBX_TEXTURE, true);
	ioSettings->SetBoolProp(EXP_FBX_EMBEDDED, true);
	ioSettings->SetBoolProp(EXP_FBX_ANIMATION, true);
	ioSettings->SetBoolProp(EXP_FBX_SHAPE, true);
	ioSettings->SetIntProp(
		EXP_FBX_EXPORT_FILE_VERSION, FBX_FILE_VERSION_7400);

	sdkManager->SetIOSettings(ioSettings);
	scene = FbxScene::Create(sdkManager, "");

	int fileNum = csvFiles.size();
	std::vector<CCSVFile*> pSrcFiles;
	for (auto& file : csvFiles)
	{
		pSrcFiles.push_back(new CCSVFile(file.c_str()));
	}

	struct PackMeshVertex
	{
		int fileId;
		int newId;
		MeshVertex* meshVertex;
	};

	std::map<int, std::vector<PackMeshVertex>> verticsMap;//CSV file iVertexID map
	int iVertexID = 0;
	//global
	std::vector<MeshVertex> remapVertexIDNew2OldVert;//newId 0, 1, 2, 3 ...

	for (int fileId = 0; fileId < fileNum; fileId++)
	{
		for (int iRow = 0; iRow < pSrcFiles[fileId]->GetRowNum(); iRow++)
		{
			pSrcFiles[fileId]->GetCellValue("IDX", iRow, iVertexID);

			auto vIter=verticsMap.begin();
			if ((vIter = verticsMap.find(iVertexID)) == verticsMap.end())
			{
				int newVertexID = remapVertexIDNew2OldVert.size();
				MeshVertex tMeshVertex;
				pSrcFiles[fileId]->GetCellValue("POSITION.x", iRow, tMeshVertex.x);
				pSrcFiles[fileId]->GetCellValue("POSITION.y", iRow, tMeshVertex.y);
				pSrcFiles[fileId]->GetCellValue("POSITION.z", iRow, tMeshVertex.z);
				if (export_normal)
				{
					pSrcFiles[fileId]->GetCellValue("NORMAL.x", iRow, tMeshVertex.nx);
					pSrcFiles[fileId]->GetCellValue("NORMAL.y", iRow, tMeshVertex.ny);
					pSrcFiles[fileId]->GetCellValue("NORMAL.z", iRow, tMeshVertex.nz);
				}
				if (export_tangent)
				{
					pSrcFiles[fileId]->GetCellValue("TANGENT.x", iRow, tMeshVertex.tx);
					pSrcFiles[fileId]->GetCellValue("TANGENT.y", iRow, tMeshVertex.ty);
					pSrcFiles[fileId]->GetCellValue("TANGENT.z", iRow, tMeshVertex.tz);
					pSrcFiles[fileId]->GetCellValue("TANGENT.w", iRow, tMeshVertex.tw);
				}
				if (export_color)
				{
					pSrcFiles[fileId]->GetCellValue("COLOR.x", iRow, tMeshVertex.cr);
					pSrcFiles[fileId]->GetCellValue("COLOR.y", iRow, tMeshVertex.cg);
					pSrcFiles[fileId]->GetCellValue("COLOR.z", iRow, tMeshVertex.cb);
					pSrcFiles[fileId]->GetCellValue("COLOR.w", iRow, tMeshVertex.ca);
				}

				if (export_uv)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD0.x", iRow, tMeshVertex.u);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD0.y", iRow, tMeshVertex.v);
				}
				if (export_uv2)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD1.x", iRow, tMeshVertex.u2);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD1.y", iRow, tMeshVertex.v2);
				}
				if (export_uv3)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD2.x", iRow, tMeshVertex.u3);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD2.y", iRow, tMeshVertex.v3);
				}
				remapVertexIDNew2OldVert.push_back(std::move(tMeshVertex));
				PackMeshVertex pMV{ fileId, newVertexID, &(remapVertexIDNew2OldVert[remapVertexIDNew2OldVert.size()-1])};
				verticsMap[iVertexID].push_back(pMV);
			}
			else//the same judge by content
			{
				bool isSame = false;
				int newId;
				pSrcFiles[fileId]->GetCellValue("IDX", iRow, iVertexID);
				
				float pX=0.f, pY=0.f, pZ=0.f, nX=0.f, nY=0.f, nZ=0.f, tX=0.f, tY=0.f, tZ=0.f, tW=0.f, cR=0.f, cG=0.f, cB=0.f, cA=0.f, u=0.f, v=0.f, u2=0.f, v2=0.f, u3=0.f, v3 = 0.f;
				pSrcFiles[fileId]->GetCellValue("POSITION.x", iRow, pX);
				pSrcFiles[fileId]->GetCellValue("POSITION.y", iRow, pY);
				pSrcFiles[fileId]->GetCellValue("POSITION.z", iRow, pZ);
				if (export_normal)
				{
					pSrcFiles[fileId]->GetCellValue("NORMAL.x", iRow, nX);
					pSrcFiles[fileId]->GetCellValue("NORMAL.y", iRow, nY);
					pSrcFiles[fileId]->GetCellValue("NORMAL.z", iRow, nZ);
				}
				if (export_tangent)
				{
					pSrcFiles[fileId]->GetCellValue("TANGENT.x", iRow, tX);
					pSrcFiles[fileId]->GetCellValue("TANGENT.y", iRow, tY);
					pSrcFiles[fileId]->GetCellValue("TANGENT.z", iRow, tZ);
					pSrcFiles[fileId]->GetCellValue("TANGENT.w", iRow, tW);
				}
				if (export_color)
				{
					pSrcFiles[fileId]->GetCellValue("COLOR.x", iRow, cR);
					pSrcFiles[fileId]->GetCellValue("COLOR.y", iRow, cG);
					pSrcFiles[fileId]->GetCellValue("COLOR.z", iRow, cB);
					pSrcFiles[fileId]->GetCellValue("COLOR.w", iRow, cA);
				}
				if (export_uv)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD0.x", iRow, u);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD0.y", iRow, v);
				}
				if (export_uv2)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD1.x", iRow, u2);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD1.y", iRow, v2);
				}
				if (export_uv3)
				{
					pSrcFiles[fileId]->GetCellValue("TEXCOORD2.x", iRow, u3);
					pSrcFiles[fileId]->GetCellValue("TEXCOORD2.y", iRow, v3);
				}
				for (auto& packMV : verticsMap[iVertexID])
				{
					if (packMV.meshVertex->x == pX && packMV.meshVertex->y == pY && packMV.meshVertex->z == pZ &&
						packMV.meshVertex->nx == nX && packMV.meshVertex->ny == nY && packMV.meshVertex->nz == nZ &&
						packMV.meshVertex->tx == tX && packMV.meshVertex->ty == tY && packMV.meshVertex->tz == tZ && packMV.meshVertex->tw == tW &&
						packMV.meshVertex->cr == cR && packMV.meshVertex->cg == cG && packMV.meshVertex->cb == cB && packMV.meshVertex->ca == cA &&
						packMV.meshVertex->u == u && packMV.meshVertex->v == v && packMV.meshVertex->u2 == u2 && packMV.meshVertex->v2 == v2 && packMV.meshVertex->u3 == u3 && packMV.meshVertex->v3 == v3)
					{
						isSame = true;
						newId = packMV.newId;
					}
				}
				if (isSame)
				{
					PackMeshVertex pMV{ fileId, newId, &(remapVertexIDNew2OldVert[newId]) };
					verticsMap[iVertexID].push_back(pMV);
				}
				else
				{
					newId = remapVertexIDNew2OldVert.size();
					MeshVertex mVert{ pX, pY, pZ, nX, nY, nZ, tX, tY, tZ, tW, cR, cG, cB, cA, u, v, u2, v2, u3, v3 };
					remapVertexIDNew2OldVert.push_back(std::move(mVert));
					PackMeshVertex pMV{ fileId, newId, &(remapVertexIDNew2OldVert[remapVertexIDNew2OldVert.size() - 1]) };
					verticsMap[iVertexID].push_back(pMV);
				}
			}
		}
	}
	int iTotalVerticsCount = remapVertexIDNew2OldVert.size();

	// 用csv的文件名作为mesh的名字
	std::string meshName = csvFiles[0];
	replace(meshName.begin(), meshName.end(), '/', '\\');
	meshName = meshName.substr(0, meshName.size() - 4);
	int pos = meshName.find_last_of('\\');
	if (pos != std::string::npos)
	{
		meshName = meshName.substr(pos + 1, meshName.size() - pos - 1);
	}

	FbxNode* rootNode = scene->GetRootNode();
	FbxNode* subshapeNode = FbxNode::Create(rootNode, meshName.c_str());

	// convert fbx mesh file
	FbxMesh* meshFbx = FbxMesh::Create(subshapeNode, subshapeNode->GetName());

	FbxGeometryElementNormal* meshNormal = NULL;
	FbxGeometryElementTangent* meshTangent = NULL;
	FbxLayerElementVertexColor* meshColor = NULL;
	FbxGeometryElementUV* meshUV = NULL;
	FbxGeometryElementUV* meshUV2 = NULL;
	FbxGeometryElementUV* meshUV3 = NULL;

	if (export_normal)
	{
		meshNormal = meshFbx->CreateElementNormal();
	}
	if (export_tangent)
	{
		meshTangent = meshFbx->CreateElementTangent();
	}
	if (export_color)
	{
		meshColor = meshFbx->CreateElementVertexColor();
	}

	if (export_uv)
	{
		meshUV = meshFbx->CreateElementUV("UV");
	}
	if (export_uv2)
	{
		meshUV2 = meshFbx->CreateElementUV("UV1");
	}
	if (export_uv3)
	{
		meshUV3 = meshFbx->CreateElementUV("UV2");
	}

	meshFbx->InitControlPoints(iTotalVerticsCount);

	if (export_normal)
	{
		meshNormal->SetMappingMode(FbxGeometryElementNormal::eByControlPoint);
		meshNormal->SetReferenceMode(FbxGeometryElementNormal::eDirect);
	}
	if (export_tangent)
	{
		meshTangent->SetMappingMode(FbxGeometryElementTangent::eByControlPoint);
		meshTangent->SetReferenceMode(FbxGeometryElementTangent::eDirect);
	}
	if (export_color)
	{
		meshColor->SetMappingMode(FbxGeometryElementTangent::eByControlPoint);
		meshColor->SetReferenceMode(FbxGeometryElementTangent::eDirect);
	}

	if (export_uv)
	{
		meshUV->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}
	if (export_uv2)
	{
		meshUV2->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV2->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}
	if (export_uv3)
	{
		meshUV3->SetMappingMode(FbxGeometryElementUV::eByControlPoint);
		meshUV3->SetReferenceMode(FbxGeometryElementUV::eDirect);
	}

	FbxVector4* meshVectors = meshFbx->GetControlPoints();
	Matrix44 matRot;
	MatrixRotationZ(&matRot, -FLT_DTOR(0));

	for (int index = 0; index < remapVertexIDNew2OldVert.size(); index++)
	{
		Vector3 Vertex(
			remapVertexIDNew2OldVert[index].x * 100, remapVertexIDNew2OldVert[index].y * 100, remapVertexIDNew2OldVert[index].z * 100);
		Vec3TransformCoord(&Vertex, &Vertex, &matRot);
		meshVectors[index].Set(Vertex.x, Vertex.y, Vertex.z);

		if (export_normal)
		{
			Vector3 VertexNormal(
				remapVertexIDNew2OldVert[index].nx, remapVertexIDNew2OldVert[index].ny, remapVertexIDNew2OldVert[index].nz);
			Vec3TransformNormal(&VertexNormal, &VertexNormal, &matRot);

			meshNormal->GetDirectArray().Add(
				FbxVector4(VertexNormal.x, VertexNormal.y, VertexNormal.z, 0));
		}
		if (export_tangent)
		{
			Vector4 VertexTangent(
				remapVertexIDNew2OldVert[index].tx, remapVertexIDNew2OldVert[index].ty, remapVertexIDNew2OldVert[index].tz, remapVertexIDNew2OldVert[index].tw);
			VertexTangent = VertexTangent * matRot;

			meshTangent->GetDirectArray().Add(
				FbxVector4(VertexTangent.x, VertexTangent.y, VertexTangent.z, VertexTangent.w));
		}
		if (export_color)
		{
			meshColor->GetDirectArray().Add(FbxVector4(remapVertexIDNew2OldVert[index].cr, remapVertexIDNew2OldVert[index].cg, remapVertexIDNew2OldVert[index].cb, remapVertexIDNew2OldVert[index].ca));
		}
		if (export_uv)
		{
			meshUV->GetDirectArray().Add(
				FbxVector2(remapVertexIDNew2OldVert[index].u, remapVertexIDNew2OldVert[index].v));
		}
		if (export_uv2)
		{
			meshUV2->GetDirectArray().Add(
				FbxVector2(remapVertexIDNew2OldVert[index].u2, remapVertexIDNew2OldVert[index].v2));
		}
		if (export_uv3)
		{
			meshUV3->GetDirectArray().Add(
				FbxVector2(remapVertexIDNew2OldVert[index].u3, remapVertexIDNew2OldVert[index].v3));
		}
	}

	
	int polygenNum = 0;
	std::vector<FbxSurfacePhong*> gMaterials;
	for (int submeshID = 0; submeshID < fileNum; submeshID++)
	{
		FbxDouble3 lColor(submeshID * 1.0 / 3.0, 0, 1);
		gMaterials.push_back(FbxSurfacePhong::Create(sdkManager, "Material" + submeshID));
		gMaterials[gMaterials.size() - 1]->Ambient.Set(lColor);
		polygenNum += (pSrcFiles[submeshID]->GetRowNum() + 1) / 3;
	}
	auto mat = meshFbx->CreateElementMaterial();
	mat->SetMappingMode(FbxGeometryElementMaterial::eByPolygon);
	mat->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
	mat->GetIndexArray().SetCount(polygenNum);


	int iFaceID = 0;
	auto FindNewFaceId = [&](int fileId, int iVertexOld) {
		for (auto& pVM : verticsMap[iVertexOld])
		{
			if (pVM.fileId == fileId)
				return pVM.newId;
		}
		return -1;
		};

	for (int submeshID = 0; submeshID < fileNum; submeshID++)
	{
		for (int iRow = 0; iRow < pSrcFiles[submeshID]->GetRowNum(); iRow += 3)
		{
			meshFbx->BeginPolygon(submeshID);

			pSrcFiles[submeshID]->GetCellValue("IDX", iRow, iFaceID);
			meshFbx->AddPolygon(FindNewFaceId(submeshID, iFaceID));
			pSrcFiles[submeshID]->GetCellValue("IDX", iRow + 1, iFaceID);
			meshFbx->AddPolygon(FindNewFaceId(submeshID, iFaceID));
			pSrcFiles[submeshID]->GetCellValue("IDX", iRow + 2, iFaceID);
			meshFbx->AddPolygon(FindNewFaceId(submeshID, iFaceID));

			meshFbx->EndPolygon();
			mat->GetIndexArray().SetAt(iRow, submeshID);
		}
		subshapeNode->AddMaterial(gMaterials[submeshID]);
	}

	subshapeNode->SetNodeAttribute(meshFbx);
	subshapeNode->SetShadingMode(FbxNode::eTextureShading);
	

	// save fbx
	std::string fbxFilePath = csvFiles[0];
	fbxFilePath = fbxFilePath.substr(0, fbxFilePath.size() - 4);
	fbxFilePath += "_merge.fbx";

	int startIndex = fbxFilePath.find_last_of('\\');
	std::string fileName = fbxFilePath.substr(startIndex + 1);

	FbxExporter* exporter = FbxExporter::Create(sdkManager, fileName.c_str());
	if (!exporter->Initialize(fbxFilePath.c_str(), -1, ioSettings))
	{
		fprintf(stderr, "Failed to initialize FBX exporter\n");
		exporter->Destroy();
		return;
	}
	exporter->SetFileExportVersion(FBX_2014_00_COMPATIBLE);

	if (!exporter->Export(scene))
	{
		fprintf(stderr, "Failed to produce FBX file\n");
		exporter->Destroy();
		return;
	}

	exporter->Destroy();

}

int main(int argc, char* argv[])
{
	bool export_normal = false;
	bool export_tangent = false;
	bool export_color = false;
	bool export_uv = false;
	bool export_uv2 = false;
	bool export_uv3 = false;

	if (argc <  6)
		return 0;

	bool mergeFBX = false;
	int mergeNum = 0;
	int normalID = 2;
	int tangentID = 3;
	int colorID = 4;
	int uvID = 5;
	int uv1ID = 6;
	int uv2ID = 7;
	std::vector<std::string> mergeFiles;
	if (strlen(argv[1]) == 1)
	{
		mergeFBX = true;
		mergeNum = atoi(argv[1]);
		normalID += mergeNum;
		tangentID += mergeNum;
		colorID += mergeNum;
		uvID += mergeNum;
		uv1ID += mergeNum;
		uv2ID += mergeNum;
		mergeFiles.resize(mergeNum);
		for (int i = 0; i < mergeNum; i++)
		{
			mergeFiles[i] = argv[2 + i];
		}
	}
	

	if (strncmp(argv[normalID], "1", 1) == 0)
	{
		export_normal = true;
	}
	if (strncmp(argv[tangentID], "1", 1) == 0)
	{
		export_tangent = true;
	}
	if (strncmp(argv[colorID], "1", 1) == 0)
	{
		export_color = true;
	}
	if (strncmp(argv[uvID], "1", 1) == 0)
	{
		export_uv = true;
	}
	if (strncmp(argv[uv1ID], "1", 1) == 0)
	{
		export_uv2 = true;
	}
	if (strncmp(argv[uv2ID], "1", 1) == 0)
	{
		export_uv3 = true;
	}

	if (!mergeFBX)
	{
		ConvertCSV2FBX(argv[1],
			export_normal, export_tangent, export_color,
			export_uv, export_uv2, export_uv3);
	}
	else
	{
		MergeCSVsToFBX(mergeFiles, export_normal, export_tangent, export_color,
			export_uv, export_uv2, export_uv3);
	}
}
