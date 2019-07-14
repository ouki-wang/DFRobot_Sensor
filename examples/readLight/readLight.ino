/*!
 * @file readLight.ino
 * @brief 读取环境光线强度，单位是勒克斯(Lux)
 * @n 实验现象：每秒读取一次环境光线强度，并打印到串口，给传感器以不同的光照强度，可以得到不同的采集结果
 * @n 由于只有4 bits存放光照强度，最低分辨率1000，所以能采集的范围是 0Lux-150000Lux
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
  /*在这里一致等到芯片初始化完成才能退出*/
  while(sensor.begin() != 0){
    Serial.println("初始化芯片失败，请确认芯片连接是否正确");
    delay(1000);
  }
}

void loop(void)
{
  /*读取光线强度*/
  uint16_t v = sensor.lightStrengthLux();
  Serial.print("Light Strength=");
  Serial.print(v);
  Serial.println(" Lux");
  delay(1000);
}
