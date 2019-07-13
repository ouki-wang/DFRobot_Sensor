/*!
 * @file readLight.ino
 * @brief 读取环境光线强度
 * @n 实验现象：每秒读取一次环境光线强度，并打印到串口
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_Sensor.h>
DFRobot_Sensor_IIC sensor(&Wire, eLowPower);
void setup(void)
{
  Serial.begin(115200);
  sensor.begin();
}

void loop(void)
{
  uint16_t v = sensor.getLightStrength();
  Serial.print("light=");
  Serial.println(v);
  delay(1000);
}