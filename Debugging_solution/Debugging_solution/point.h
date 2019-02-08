#ifndef point_h
#define point_h

class POINT
{
public:
	POINT(float x, float y);
	POINT();
	~POINT();
	float get_x_coord();
	float get_y_coord();
	void set_x_coord(float x);
	void set_y_coord(float y);
private:
	float x;
	float y;
};

#endif