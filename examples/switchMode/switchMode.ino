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
//默认以低功耗模式工作
DFRobot_Sensor_SPI sensor(&SPI, /*cs=*/13, DFRobot_Sensor_SPI::eLowPower);

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
  int ret;
  //为了完成xxx任务，先切换到正常功耗模式, 
  if((ret = sensor.switchMode(sensor.eNormalPower)) != 0){
    Serial.print("切换到eNormalPower失败 ret=");
    Serial.println(ret);
  }
  //为了完成xxx任务，切换到高速度模式
  if((ret = sensor.switchMode(sensor.eHighSpeed)) != 0){
    Serial.print("切换到eNormalPower失败 ret=");
    Serial.println(ret);
  }
  //为了完成xxx任务，切换到正常速度模式
  if((ret = sensor.switchMode(sensor.eNormalSpeed)) != 0){
    Serial.print("切换到eNormalPower失败 ret=");
    Serial.println(ret);
  }
  //为了完成xxx任务，切换到低功耗模式
  if((ret = sensor.switchMode(sensor.eLowPower)) != 0){
    Serial.print("切换到eNormalPower失败 ret=");
    Serial.println(ret);
  }
  //为了完成xxx任务，切换到eNormalPower+eHighSpeed模式
  if((ret = sensor.switchMode(sensor.eNormalPower+sensor.eHighSpeed)) != 0){
    Serial.print("切换到eNormalPower+eHighSpeed失败 ret=");
    Serial.println(ret);
  }
  //为了完成xxx任务，切换到eHighPrecision+eNormalSpeed模式
  if((ret = sensor.switchMode(sensor.eHighPrecision+sensor.eNormalSpeed)) != 0){
    Serial.print("切换到eHighPrecision+eNormalSpeed失败 ret=");
    Serial.println(ret);
  }

  uint16_t v = sensor.soundStrengthDB();
  Serial.print("sound strength=");
  Serial.println(v);
  Serial.println(" dB");
  delay(1000);
}
