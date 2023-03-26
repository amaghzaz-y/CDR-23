#include <Arduino.h>
#include <types/Steps.h>
class ActorSystem
{
public:
	TaskHandle_t TaskLidar;
	TaskHandle_t TaskMovement;
	TaskHandle_t TaskMain;
	ActorSystem();
	void setup();
	TaskHandle_t createLidarActor();
	TaskHandle_t createMovementTask(Steps steps);
	void schedule();
};