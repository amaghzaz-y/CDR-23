#include <types/PolarVec.h>
#include <core/Lidar.h>
class LidarActor
{
private:
	PolarVec vec;
	TaskHandle_t task;

public:
	LidarActor();
	TaskHandle_t createTask();
};