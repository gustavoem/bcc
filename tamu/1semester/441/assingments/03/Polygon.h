#ifndef POLYGON_H_
#define POLYGON_H_

class Polygon
{

private:

	// Stores the first point that defined the polygon
	//
	pair <unsigned int, unsigned int> first point;


	// Storest the scan_line of the polygon
	//
	map<unsigned int, vector<unsigned int> > scan_lines;

public:

	// Default constructor. Receives the first point as an argument
	//
	Polygon (pair<unsigned int, unsigned int>);


	// Default destructor
	//
	virtual ~Polygon ();


	// Receives a new point
	//
	void newPoint (pair<unsigned int, unsigned int>);


	// Closes the polygon
	//
	void closePolygon (pair<unsigned int, unsigned int>);


	// Returns the scan list of the polygon
	//
	map<unsigned int, vector<unsigned int> > getScanLines ();	


};

#endif