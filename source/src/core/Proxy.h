#include <lib/SoftwareSerial/SoftwareSerial.h>
#include <types/Point2D.h>
#define RXPIN 12
#define TXPIN 13

class Proxy
{
private:
	Point2D currentPoint;
	bool lidarState;
	bool sensorA;
	bool sensorB;
	bool sensorC;
	bool pickSideA;
	bool pickSideB;
	bool pickSideC;
	int levelSideA;
	int levelSideB;
	int levelSideC;
	int currentScore;
	EspSoftwareSerial::UART _serial;

public:
	// setters
	void setCurrentPoint(Point2D point);
	void setLidarState(bool state);
	void setSensorState(int sensorID, bool state);
	void setGripperState(int gripperID, bool state);
	void setGripperLevel(int gripperID, int level);
	void setCurrentScore(int score);
	// getters
	void getCurrentPoint();
	void getLidarState();
	void getGripperState(int gripperID);
	void getGripperLevel(int gripperID);
	void getCurrentScore();
	String getState();
	void update(String msg);
	// setup
	void setup(int CARD);
	void start(int CARD);
};