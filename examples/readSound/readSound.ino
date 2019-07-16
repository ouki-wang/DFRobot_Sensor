/*!
 * @file readSound.ino
 * @brief 读取环境声音强度，单位DB
 * @n 实验现象：每秒读取一次环境光线强度，并打印到串口
 * @n 给传感器以不同的光照强度，可以得到不同的采集结果
 * @n 由于只有4 bits存放声音强度，最低分辨率8dB，所以测量范围是 0dB-120dB
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
//DFRobot_Sensor_IIC sensor;//这样定义会使用默认参数，&Wire  eNomalPrecision+eNormalSpeed+eNormalPower

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
  uint16_t soundStrength = sensor.soundStrengthDB();
  Serial.print("sound strength=");
  Serial.print(soundStrength);
  Serial.println(" dB");
  delay(1000);
}