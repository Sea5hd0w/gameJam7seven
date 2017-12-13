#include "Element.h"

#include "LibraryCommunication.h"
#include "GlobalVariable.h"

#include "View.h"



Element::Element(World* world, long iDIsland, long iDDimension, tuple<long, long, long> point, bool permeability, string sprite, int orientation, int priority)
	: world(world), iDIsland(iDIsland), iDDimension(iDDimension), point(point), permeability(permeability), orientation(orientation), priority(priority), pathSprite(sprite)
{
	this->p_sprite = Sprites::addSprite(sprite);
	this->sprite = {0,0, 128,128};
	this->xSize = 128;
	this->ySize = 128;
	gen("[(" + to_string(get<0>(point)) + "," + to_string(get<1>(point)) + "," + to_string(get<2>(point)) + ")] : " + __func__ + " : Create");

	this->t = clock();
}


Element::~Element()
{
	Sprites::deleteSprite(this->pathSprite);
	des("[(" + to_string(get<0>(point)) + "," + to_string(get<1>(point)) + "," + to_string(get<2>(point)) + ")] : " + typeid(this).name() + " : Delete");
}

const tuple<long, long, long> Element::getPoint() {
	return this->point;
}

const bool Element::getPermeability() {
	return this->permeability;
}

const int Element::getOrientation() {
	return this->orientation;
}

void Element::printSprite(int xPosition, int yPosition)
{
	SDL_Rect dest = { xPosition, yPosition, this->xSize, this->ySize};
	try {
		SDL_RenderCopy(View::renderer, this->p_sprite, &this->sprite, &dest);
	}
	catch (exception)
	{
	}
}

World* Element::getWorld()
{
	return this->world;
}

long Element::getIDDimension()
{
	return this->iDDimension;
}

long Element::getIDIsland()
{
	return this->iDIsland;
}

const long Element::getX()
{
	return get<0>(point);
}

const long Element::getY()
{
	return get<1>(point);
}

const long Element::getZ()
{
	return get<2>(point);
}

pair<tuple<long*, long, long*, long*>, Element*> Element::getElementToView()
{
	return make_pair(this->getIDElementToView(), this);
}

tuple<long*, long, long*, long*> Element::getIDElementToView()
{
	return make_tuple(&get<2>(this->point), this->priority, &get<0>(this->point), &get<1>(this->point));
}

void Element::setPoint(tuple<long, long, long> new_point) {
	this->point = new_point;
}

void Element::setPermeability(bool new_permeability) {
	this->permeability = new_permeability;
}

void Element::setOrientation(int new_orientation) {
	if (new_orientation >= 0 && new_orientation < 8)
	{
		this->orientation = new_orientation;
	}
}

void Element::setIDDimension(long new_IDDImension)
{
	this->iDDimension = new_IDDImension;
}

void Element::move()
{
	//do nothing
}