#pragma once

#include <string>
#include <tuple>
#include <list>
#include "SDL.h"

#include "Element.h"
class Mobile;

class MotionLess : public Element {
public:
	MotionLess(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, long iDMotionLess);
	~MotionLess();

	const long getIDMotionLess();

	static MotionLess* getMotionLess(long iDMotionLess, World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite);

	virtual void enable(); 
	virtual void disable();

	virtual void walkOn(Mobile* mobile); //Interac with MotionLess
	virtual void walkOff(Mobile* mobile); //Interac with MotionLess

protected:
	void setIDMotionLess(long new_IDMotionLessElement); // Setter

	virtual void Notify(bool onOff); //Recive notification

private:
	long iDMotionLess;

	static MotionLess* GetHole(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess Hole = 1
	static MotionLess* GetFloor(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess Floor = 2
	static MotionLess* GetBlock(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess Block = 3
	static MotionLess* GetSlopeUpRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeUpRight = 4
	static MotionLess* GetSlopeUpLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeUpLeft = 5
	static MotionLess* GetSlopeDownRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeDownRight = 6
	static MotionLess* GetSlopeDownLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeDownLeft = 7
	static MotionLess* GetLadderUpRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess LadderUpRight = 8	
	static MotionLess* GetLadderUpLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeUpLeft = 9
	static MotionLess* GeLadderDownRight(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeDownRight = 10
	static MotionLess* GetLadderDownLeft(World* world, SOCKControler* controler, long iDIsland, long iDDimension, tuple<long, long, long> point, string sprite); //ID_MotionLess SlopeDownLeft = 11
};

