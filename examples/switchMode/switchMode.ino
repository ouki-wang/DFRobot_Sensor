/*!
 * @file switchMode.ino
 * @brief 各种模式切换
 * @n 实验现象：演示各种模式切换，保证板子正常工作
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_Sensor.h>
DFRobot_Sensor_SPI sensor(&SPI, 13, eLowPower);
void setup(void)
{
  Serial.begin(115200);
  sensor.begin();
}

void loop(void)
{
  sensor.switchMode(eNormalPower);
  sensor.switchMode(eLowPower);
  sensor.switchMode(eNormalSpeed);
  sensor.switchMode(eHighSpeed);
  sensor.switchMode(eNormalPower+eNormalSpeed);
  sensor.switchMode(eLowPower+eHighSpeed);
  uint16_t v = sensor.getSoundStrength();
  Serial.print("sound=");
  Serial.println(v);
  delay(1000);
}