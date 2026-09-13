//----------------------------------------------------------------------
// MStopZoneRectEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStopZoneRectEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"
#include "SkillDef.h"

//#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MStopZoneRectEffectGenerator	g_StopZoneRectEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MStopZoneRectEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK = false;
	bool bAdd;

	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;
	BYTE			power = egInfo.power;

	//-----------------------------------------------------------
	// ��ũ�Ͻ��� ��� �پ��ϰ� ����ֱ�...
	// �ӽ� ���� �ڵ�.. ����~
	//-----------------------------------------------------------
	BOOL bDarkness = FALSE, bGrayDarkness = FALSE, bSharpHail = FALSE;
	if (frameID>=EFFECTSPRITETYPE_DARKNESS_1_1
		&& frameID<=EFFECTSPRITETYPE_DARKNESS_3_5 ||
		frameID >= EFFECTSPRITETYPE_GRAY_DARKNESS_1_1 &&
		frameID <= EFFECTSPRITETYPE_GRAY_DARKNESS_3_5 )
	{
		if (egInfo.pPreviousEffect!=NULL)
		{
			TYPE_FRAMEID oldFrameID = (egInfo.pPreviousEffect)->GetFrameID();

			frameID = oldFrameID + 5;
		}
		else
		{
			if (frameID>=EFFECTSPRITETYPE_DARKNESS_1_1
				&& frameID<=EFFECTSPRITETYPE_DARKNESS_1_5)
			{
				frameID = EFFECTSPRITETYPE_DARKNESS_1_1 + rand()%5;
			}
			else if (frameID >= EFFECTSPRITETYPE_GRAY_DARKNESS_1_1 &&
				frameID <= EFFECTSPRITETYPE_GRAY_DARKNESS_1_5 )
			{
				frameID = EFFECTSPRITETYPE_GRAY_DARKNESS_1_1 + rand()%5;
			}
			/*
			else if (frameID>=EFFECTSPRITETYPE_DARKNESS_2_1
				&& frameID<=EFFECTSPRITETYPE_DARKNESS_2_5)
			{
				frameID = EFFECTSPRITETYPE_DARKNESS_2_1 + rand()%5;
			}
			
			else if (frameID>=EFFECTSPRITETYPE_DARKNESS_3_1
				&& frameID<=EFFECTSPRITETYPE_DARKNESS_3_5)
			{
				frameID = EFFECTSPRITETYPE_DARKNESS_3_1 + rand()%5;
			}
			*/
		}

		if( frameID >= EFFECTSPRITETYPE_DARKNESS_1_1 &&
			frameID <= EFFECTSPRITETYPE_DARKNESS_3_5 )
			bDarkness = TRUE;
		else
			bGrayDarkness = TRUE;
//		int kkk = RESULT_MAGIC_DARKNESS_WIDE, kkk2 = RESULT_MAGIC_DARKNESS;
		if(egInfo.nActionInfo == RESULT_MAGIC_DARKNESS_WIDE ||
			egInfo.nActionInfo == RESULT_SKILL_WIDE_GRAY_DARKNESS )
			power = 2;
	}
	else if(frameID == EFFECTSPRITETYPE_NEW_SHARP_HAIL_DROP_1) // 2006.02.17 chyaya		EFFECTSPRITETYPE_SHARP_HAIL_DROP_1)
	{
		bSharpHail = TRUE;
		power = 2;
	}

	//---------------------------------------------
	// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
	//---------------------------------------------
	TYPE_SECTORPOSITION	sX, sY;
	sX = g_pTopView->PixelToMapX(egInfo.x0);
	sY = g_pTopView->PixelToMapY(egInfo.y0);

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MEffect*	pEffect;
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	pEffect = new MEffect(bltType);

	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPosition(sX, sY);		// Sector ��ǥ		
	pEffect->SetZ(egInfo.z0);			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
	pEffect->SetCount( egInfo.count , egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(power);

	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	bAdd = g_pZone->AddEffect( pEffect );

	// ���� Effect ���� ����
	if (bAdd)
	{
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

		bOK = true;
	}	
	
//	int sX1 = sX-power;
//	int sY1 = sY-power;
//	int sX2 = sX+power;
//	int sY2 = sY+power;

	if(egInfo.nActionInfo == SKILL_WIDE_ICE_FIELD)
	{
		power = 2;
//		sX1 = sX-2;
//		sY1 = sY-2;
//		sX2 = sX+2;
//		sY2 = sY+2;
	}
	else if(egInfo.nActionInfo == SKILL_LAND_MINE_EXPLOSION)
	{
		power = 3;
//		sX1 = sX-3;
//		sY1 = sY-3;
//		sX2 = sX+3;
//		sY2 = sY+3;

	}

	// Ruper Island: Palus Long Range Magic's result record sits in action slot 155 + MinResult
	// (Packet/Gpackets/ServerSkillDisplay.h). The server hits a 5x5 area, so draw 5x5.
	if (g_pActionInfoTable != NULL
		&& egInfo.nActionInfo == (int)(*g_pActionInfoTable).GetMinResultActionInfo() + 155)
	{
		power = 2;
	}

	int sX1 = sX-power;
	int sY1 = sY-power;
	int sX2 = sX+power;
	int sY2 = sY+power;

	//------------------------------------------------------
	// Zone�� ������ �ƴ� ��쿡 Skip...
	//------------------------------------------------------
	if (sX1 < 0) 
	{					
		sX1 = 0;	
	}

	if (sX2 >= g_pZone->GetWidth())
	{
		sX2 = g_pZone->GetWidth()-1;
	}

	if (sY1 < 0)
	{
		sY1 = 0;	
	}

	if (sY2 >= g_pZone->GetHeight())
	{
		sY2 = g_pZone->GetHeight()-1;
	}


	// Tile���� �ϳ��� ����
	MEffectTarget*	pEffectTarget2;
	
	DWORD TempDelay = 0;
	int x, y;
	for (y=sY1; y<=sY2; y++)
	{
		for (x=sX1; x<=sX2; x++)
		{
			if (x==sX && y==sY)
				continue;

			TempDelay = 0;
			//--------------------------------------------------------------
			// Darkness�� ��� - �ӽ� �ڵ�.. - -;;
			//--------------------------------------------------------------
			if (bDarkness)
			{
				frameID = EFFECTSPRITETYPE_DARKNESS_1_1 + rand()%5;
			} 
			else if( bGrayDarkness )
			{
				frameID = EFFECTSPRITETYPE_GRAY_DARKNESS_1_1 + rand()%5;
			}
			else if ( bSharpHail )
			{
				frameID = EFFECTSPRITETYPE_NEW_SHARP_HAIL_DROP_1 + rand() %3 ; // 2006.02.17 chyaya  EFFECTSPRITETYPE_SHARP_HAIL_DROP_1 + rand()%3;
			}
			
			pEffect = new MEffect(bltType);
	
			pEffect->SetFrameID( frameID, maxFrame );	

			pEffect->SetPosition(x, y);		// Sector ��ǥ	
			pEffect->SetZ(egInfo.z0);			
			pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.	
			pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

			// ���� ����
			pEffect->SetDirection( egInfo.direction );

			// ����
			pEffect->SetPower(power);

			// ���� ���
			//pEffect->SetLight( light );

			 if(egInfo.nActionInfo == SKILL_LAND_MINE_EXPLOSION || bSharpHail )
			 {
				TempDelay = rand()%16;
				pEffect->SetWaitFrame(TempDelay);
				pEffect->SetCount( egInfo.count + TempDelay, egInfo.linkCount );			// ���ӵǴ� Frame

			 }
			// Zone�� �߰��Ѵ�.
			bAdd = g_pZone->AddEffect( pEffect, TempDelay);

			if (bAdd)
			{
				// parameter�� ���� effectTarget�� �����ؾ� �ϴ� ���
				if (!bOK)
				{
					pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

					bOK = true;
				}
				else
				{
					// ���� Effect ���� ����
					if (egInfo.pEffectTarget == NULL)
					{
						pEffect->SetLink( egInfo.nActionInfo, NULL );
					}
					else
					{
						pEffectTarget2 = new MEffectTarget(*egInfo.pEffectTarget);
						pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
						pEffectTarget2->Set( egInfo.x1+TILE_X*(x-sX1-1), 
												egInfo.y1+TILE_Y*(y-sY1-1), 
												egInfo.z0, 
												egInfo.creatureID );
					}
				}
			}

			/*
			if (bAdd)
			{
				int num = rand() % maxFrame;
				
				for (int nf=0; nf<num; nf++)
				{
					pEffect->NextFrame();
				}
			}
			*/

			//bOK = bOK || bAdd;
		}
	}

	return bOK;
}
